#include "Logger.h"

#include <stdio.h>
#include <ctype.h>

ImGuiAl::Fifo::Fifo(void* const buffer, size_t const size)
    : _buffer(buffer)
    , _size(size)
    , _available(size)
    , _first(0)
    , _last(0) {}

void ImGuiAl::Fifo::reset() {
    _available = _size;
    _first = _last = 0;
}

void ImGuiAl::Fifo::read(void* const data, size_t const count) {
    size_t first_batch = count;
    size_t second_batch = 0;

    if (first_batch > _size - _first) {
        first_batch = _size - _first;
        second_batch = count - first_batch;
    }

    uint8_t const* const src = static_cast<uint8_t const*>(_buffer) + _first;
    memcpy(data, src, first_batch);
    memcpy(static_cast<uint8_t*>(data) + first_batch, _buffer, second_batch);

    _first = (_first + count) % _size;
    _available += count;
}

void ImGuiAl::Fifo::peek(size_t const pos, void* const data, size_t const count) const {
    size_t const position = (pos + _first) % _size;
    size_t first_batch = count;
    size_t second_batch = 0;

    if (first_batch > _size - position) {
        first_batch = _size - position;
        second_batch = count - first_batch;
    }

    uint8_t const* const src = static_cast<uint8_t const*>(_buffer) + position;
    memcpy(data, src, first_batch);
    memcpy(static_cast<uint8_t*>(data) + first_batch, _buffer, second_batch);
}

void ImGuiAl::Fifo::write(void const* const data, size_t const count) {
    size_t first_batch = count;
    size_t second_batch = 0;

    if (first_batch > _size - _last) {
        first_batch = _size - _last;
        second_batch = count - first_batch;
    }

    uint8_t* const dest = static_cast<uint8_t*>(_buffer) + _last;
    memcpy(dest, data, first_batch);
    memcpy(_buffer, static_cast<uint8_t const*>(data) + first_batch, second_batch);

    _last = (_last + count) % _size;
    _available -= count;
}

void ImGuiAl::Fifo::skip(size_t const count) {
    _first = (_first + count) % _size;
    _available += count;
}

ImGuiAl::Crt::Crt(void* const buffer, size_t const size)
    : _fifo(buffer, size)
    , _foregroundColor(CGA::White)
    , _metaData(0)
    , _scrollToBottom(false) {}

void ImGuiAl::Crt::setForegroundColor(ImU32 const color) {
    _foregroundColor = color;
}

void ImGuiAl::Crt::setMetaData(unsigned const meta_data) {
    _metaData = meta_data;
}

void ImGuiAl::Crt::printf(char const* const format, ...) {
    va_list args;
    va_start(args, format);
    vprintf(format, args);
    va_end(args);
}

void ImGuiAl::Crt::vprintf(char const* const format, va_list args) {
    char temp[256];
    char* line = temp;

    va_list args_copy;
    va_copy(args_copy, args);

    // TODO does vsnprintf ever return a negative value?
    size_t const needed = ::vsnprintf(temp, sizeof(temp), format, args);
    va_end(args);

    size_t const length = std::min(needed, _fifo.size() - sizeof(Info));

    if (length >= sizeof(temp)) {
        line = new char[length + 1];
        ::vsnprintf(line, length, format, args_copy);
    }

    va_end(args_copy);

    while (length + sizeof(Info) > _fifo.available()) {
        Info header;
        _fifo.read(&header, sizeof(header));
        _fifo.skip(header.length);
    }

    Info header;
    header.foregroundColor = _foregroundColor;
    header.length = length;
    header.metaData = _metaData;

    _fifo.write(&header, sizeof(header));
    _fifo.write(line, length);

    if (line != temp) {
        delete[] line;
    }
}

void ImGuiAl::Crt::scrollToBottom() {
    _scrollToBottom = true;
}

void ImGuiAl::Crt::clear() {
    _fifo.reset();
}

void ImGuiAl::Crt::iterate(const std::function<bool(Info const& header, char const* const line)>& iterator) const {
    size_t const occupied = _fifo.occupied();
    size_t pos = 0;

    char temp[256];
    char* line = temp;
    size_t max_length = sizeof(temp);

    while (pos < occupied) {
        Info header;
        _fifo.peek(pos, &header, sizeof(header));
        pos += sizeof(header);

        if (header.length >= max_length) {
            max_length = header.length + 1;
            char* new_line = static_cast<char*>(line == temp ? malloc(max_length) : realloc(line, max_length));

            if (new_line == nullptr) {
                if (line != temp) {
                    free(line);
                }

                break;
            }

            line = new_line;
        }

        _fifo.peek(pos, line, header.length);
        pos += header.length;
        line[header.length] = 0;

        if (!iterator(header, line)) {
            break;
        }
    }

    if (line != temp) {
        free(line);
    }
}

int ImGuiAl::Log::draw(ImVec2 const& size) {
    int action = 0;

    Crt::draw(size, [this](Info const& header, char const* const line) -> bool {
        unsigned const level = static_cast<unsigned>(_level);

        bool show = (_cumulative && header.metaData >= level) || header.metaData == level;
        show = show && _filter.PassFilter(line);

        return show;
        });

    return action;
}

void ImGuiAl::Crt::draw(ImVec2 const& size) {
    draw(size, [](Info const& header, char const* const line) -> bool {
        (void)header;
        (void)line;
        return true;
        });
}

void ImGuiAl::Crt::draw(ImVec2 const& size, const std::function<bool(Info const& header, char const* const line)>& filter) {
    char id[64];
    snprintf(id, sizeof(id), "ImGuiAl::Crt@%p", this);

    ImGui::BeginChild(id, size, false, ImGuiWindowFlags_HorizontalScrollbar);
    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(4.0f, 1.0f));

    iterate([&filter](Info const& header, char const* const line) -> bool {
        if (filter(header, line)) {
            ImGui::PushStyleColor(ImGuiCol_Text, header.foregroundColor);
            ImGui::TextUnformatted(line);
            ImGui::PopStyleColor();
        }

        return true;
        });

    if (_scrollToBottom) {
        ImGui::SetScrollHere();
        _scrollToBottom = false;
    }

    ImGui::PopStyleVar();
    ImGui::EndChild();
}

static ImU32 changeValue(ImU32 const color, float const delta_value) {
    ImVec4 rgba = ImGui::ColorConvertU32ToFloat4(color);

    float h, s, v;
    ImGui::ColorConvertRGBtoHSV(rgba.x, rgba.y, rgba.z, h, s, v);
    v += delta_value;

    if (v < 0.0f) {
        v = 0.0f;
    }
    else if (v > 1.0f) {
        v = 1.0f;
    }

    ImGui::ColorConvertHSVtoRGB(h, s, v, rgba.x, rgba.y, rgba.z);
    return ImGui::ColorConvertFloat4ToU32(rgba);
}

ImGuiAl::Log::Log(void* const buffer, size_t const buffer_size)
    : Crt(buffer, buffer_size)
    , _level(Level::Debug)
    , _cumulative(true) {

    setColor(Level::Debug, CGA::BrightBlue);
    setColor(Level::Info, CGA::BrightGreen);
    setColor(Level::Warning, CGA::Yellow);
    setColor(Level::Error, CGA::BrightRed);
}

void ImGuiAl::Log::debug(char const* const format, ...) {
    va_list args;
    va_start(args, format);
    debug(format, args);
    va_end(args);
}

void ImGuiAl::Log::info(char const* const format, ...) {
    va_list args;
    va_start(args, format);
    info(format, args);
    va_end(args);
}

void ImGuiAl::Log::warning(char const* const format, ...) {
    va_list args;
    va_start(args, format);
    warning(format, args);
    va_end(args);
}

void ImGuiAl::Log::error(char const* const format, ...) {
    va_list args;
    va_start(args, format);
    error(format, args);
    va_end(args);
}

void ImGuiAl::Log::debug(char const* const format, va_list args) {
    setForegroundColor(_debugTextColor);
    setMetaData(static_cast<unsigned>(Level::Debug));
    vprintf(format, args);
}

void ImGuiAl::Log::info(char const* const format, va_list args) {
    setForegroundColor(_infoTextColor);
    setMetaData(static_cast<unsigned>(Level::Info));
    vprintf(format, args);
}

void ImGuiAl::Log::warning(char const* const format, va_list args) {
    setForegroundColor(_warningTextColor);
    setMetaData(static_cast<unsigned>(Level::Warning));
    vprintf(format, args);
}

void ImGuiAl::Log::error(char const* const format, va_list args) {
    setForegroundColor(_errorTextColor);
    setMetaData(static_cast<unsigned>(Level::Error));
    vprintf(format, args);
}

void ImGuiAl::Log::setColor(Level const level, ImU32 const color) {
    ImU32 const button_color = changeValue(color, -0.2f);
    ImU32 const hovered_color = changeValue(color, -0.1f);

    switch (level) {
    case Level::Debug:
        _debugTextColor = color;
        _debugButtonColor = button_color;
        _debugButtonHoveredColor = hovered_color;
        break;

    case Level::Info:
        _infoTextColor = color;
        _infoButtonColor = button_color;
        _infoButtonHoveredColor = hovered_color;
        break;

    case Level::Warning:
        _warningTextColor = color;
        _warningButtonColor = button_color;
        _warningButtonHoveredColor = hovered_color;
        break;

    case Level::Error:
        _errorTextColor = color;
        _errorButtonColor = button_color;
        _errorButtonHoveredColor = hovered_color;
        break;
    }
}