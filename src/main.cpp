#include "il2cpp-appdata.h"
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <d3d11.h>
#include "imgui.h"
#include "imgui_impl_win32.h"
#include "imgui_impl_dx11.h"
#include "BetterData.h"
#include "D3D11Hooking.hpp"
#include <detours.h>
#include "helpers.h"
#include "Logger.h"
#pragma comment(lib, "detours.lib")
#pragma comment(lib, "d3d11.lib")

using namespace app;

typedef GameData_IHEKEPMDGIJ PlayerInfo;
typedef OPIJAMILNFD GameOptions;

extern const LPCWSTR LOG_FILE = L"il2cpp-log.txt";

char buffbaby[4096];
ImGuiAl::Log output(static_cast<void*>(buffbaby), sizeof(buffbaby));

IDXGISwapChain* SwapChain;
ID3D11Device* Device;
ID3D11DeviceContext* Ctx;
ID3D11RenderTargetView* RenderTargetView;

D3D_PRESENT_FUNCTION D3DPresentFunc;
WNDPROC WndProcFunc;
void (*KeyboardJoystickFunc)(KeyboardJoystick*, MethodInfo*);
void (*VoteBanSystemFunc)(VoteBanSystem*, MethodInfo*);
void (*CameraFireFunc)(Camera*, MethodInfo*);
void (*ShipStatusFunc)(ShipStatus*, MethodInfo*);


//meetinghud MHLGKMMIIOM
//meetinghud OLAAAIBODFJ

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

HWND Window;
bool menu = false;
bool ImGuiInit = false;
bool firstGo = true;
bool zero = false;
bool logData = true;
bool fullLight = false;
bool spamMeet = false;
bool noclip = false;
bool ghostmode = false;
static int tab = 0;
static float killTimer = 0;
static float speed = 0;
static float reportdist = 0;
static float speedmult = 0;
static float emcool = 0;
static float lightradius = 0;
static float mapscale = 0;
static int remainingem = 0;
static int hat = 0;
static int skin = 0;
static int color = 0;
static int pet = 0;
static int playerID = 0;
bool frozen = false;
BYTE pid = 0;
PlayerControl* pControl = nullptr;
PlayerPhysics* pPhysics = nullptr;
PlayerInfo* pInfo = nullptr;
CustomNetworkTransform* pCNT = nullptr;
GameOptions* gameOptions = nullptr;
VoteBanSystem* voteban = nullptr;
ShipStatus* ship = nullptr;


std::vector<uint8_t> dead = std::vector<uint8_t>();
std::vector<uint8_t> imp = std::vector<uint8_t>();
std::vector<String*> ban = std::vector<String*>();
std::wstring_convert<std::codecvt_utf8_utf16<char16_t, 0x10FFFF,
	std::codecvt_mode::little_endian>, char16_t> UTF16_TO_UTF8;

std::string hexify(int decimal) {
	std::stringstream sstr;
	sstr << std::hex << decimal;
	std::string HEX = sstr.str();
	return HEX;
}

std::string concate(bool newLine, const char* one, const char* two, const char* three = "", const char* four = "") {
	std::string s;
	s += one;
	s += two;
	s += three;
	s += four;
	if (newLine)
		s += "\n";
	return s;
}

std::string getNetString(String* string) {
	uint16_t* buffer = new uint16_t[string->fields.m_stringLength + 1];
	memcpy(buffer, &string->fields.m_firstChar, string->fields.m_stringLength * sizeof(uint16_t));
	buffer[string->fields.m_stringLength] = L'\0';
	std::string final = UTF16_TO_UTF8.to_bytes((const char16_t*)buffer);
	delete[] buffer;
	return final;
}

String* netString(const char* string) {
	return Marshal_PtrToStringAnsi((void*)string, NULL);
}

void logGarbage() {
	if (!inGame) {
		dead.clear();
		imp.clear();
	}
	if (getPlayers().size() > 0 && inGame) {
		for (auto p : getPlayers()) {
			if (PlayerControl_get_Data(p, NULL)->fields.DMFDFKEJHLH) {
				if (std::find(dead.begin(), dead.end(), PlayerControl_get_Data(p, NULL)->fields.FIOIBHIDDOC) != dead.end()) {
				}
				else {
					output.error(concate(false, getNetString(PlayerControl_get_Data(p, NULL)->fields.EKHEPECKPKK).c_str(), " has been killed.").c_str());
					dead.push_back(PlayerControl_get_Data(p, NULL)->fields.FIOIBHIDDOC);
				}
			}
			if (PlayerControl_get_Data(p, NULL)->fields.LODLBBJNGKB) {
				if (std::find(imp.begin(), imp.end(), PlayerControl_get_Data(p, NULL)->fields.FIOIBHIDDOC) != imp.end()) {
				}
				else {
					output.warning(concate(false, getNetString(PlayerControl_get_Data(p, NULL)->fields.EKHEPECKPKK).c_str(), " is an imposter.").c_str());
					imp.push_back(PlayerControl_get_Data(p, NULL)->fields.FIOIBHIDDOC);
				}
			}
		}
	}
}

void breakServer() {
	if (getPlayers().size() > 0 && inGame) {
		for (auto p : getPlayers()) {
			if (p != nullptr) {
				PlayerControl_CmdReportDeadBody(PlayerControl_get_Data(p, NULL)->fields.OOGBDGNGIEM, PlayerControl_get_Data(p, NULL), NULL);
			}
		}
	}
}

void kick(PlayerControl* player) {
	if (voteban != nullptr) {
		InnerNetClient* internet = (InnerNetClient*)(AmongUsClient__TypeInfo)->static_fields->Instance;
		int32_t backup = internet->fields.ClientId;

		if (getPlayers().size() > 0 && inGame) {
			for (auto p : getPlayers()) {
				for (auto p : getPlayers())
				{
					internet->fields.ClientId = InnerNetClient_GetClientIdFromCharacter(internet, (InnerNetObject*)p, NULL);
					VoteBanSystem_CmdAddVote(voteban, InnerNetClient_GetClientIdFromCharacter(internet, (InnerNetObject*)player, NULL), NULL);
				}
			}
		}

		internet->fields.ClientId = backup;
	}
}

void getPlayer(uint8_t id) {
	if (getPlayers().size() > 0 && inGame) {
		for (auto p : getPlayers()) {
			if (p != nullptr) {
				if (PlayerControl_get_Data(p, NULL) != nullptr && PlayerControl_get_Data(p, NULL)->fields.FIOIBHIDDOC == id) {
					PlayerControl* player = (PlayerControl*)((BYTE*)PlayerControl_get_Data(p, NULL)->fields.OOGBDGNGIEM - 0x4);
					PlayerInfo* playerI = PlayerControl_get_Data(p, NULL);
					CustomNetworkTransform* cnt = nullptr;
					if(player !=nullptr)
						cnt = (CustomNetworkTransform*)((BYTE*)player->fields.NetTransform);
					if (playerI != nullptr) {
						ImGui::TextColored(ImVec4(147 / 255.0f, 112 / 255.0f, 219 / 255.0f, 1), concate(false, "Name: ", getNetString(playerI->fields.EKHEPECKPKK).c_str()).c_str());
						ImGui::TextColored(ImVec4(147 / 255.0f, 112 / 255.0f, 219 / 255.0f, 1), "Host: ");
						if (id == 0) {
							ImGui::SameLine(0.0f, 1.0f); ImGui::TextColored(ImVec4(0, 1, 0, 1), "true");
						}
						else {
							ImGui::SameLine(0.0f, 1.0f); ImGui::TextColored(ImVec4(1, 0, 0, 1), "false");
						}
						ImGui::TextColored(ImVec4(147 / 255.0f, 112 / 255.0f, 219 / 255.0f, 1), "Imposter: ");
						ImGui::SameLine(0.0f, 1.0f);
						if (playerI->fields.LODLBBJNGKB) {
							ImGui::TextColored(ImVec4(0, 1, 0, 1), "true");
						}
						else {
							ImGui::TextColored(ImVec4(1, 0, 0, 1), "false");
						}
						ImGui::TextColored(ImVec4(147 / 255.0f, 112 / 255.0f, 219 / 255.0f, 1), "Dead: ");
						ImGui::SameLine(0.0f, 1.0f);
						if (playerI->fields.DMFDFKEJHLH) {
							ImGui::TextColored(ImVec4(0, 1, 0, 1), "true");
						}
						else {
							ImGui::TextColored(ImVec4(1, 0, 0, 1), "false");
						}
						ImGui::TextColored(ImVec4(147 / 255.0f, 112 / 255.0f, 219 / 255.0f, 1), "Hat: ");
						ImGui::SameLine(0.0f, 1.0f); ImGui::TextColored(ImVec4(147 / 255.0f, 112 / 255.0f, 219 / 255.0f, 1), Hats[playerI->fields.LJNAHAIMDOC].c_str());
						ImGui::TextColored(ImVec4(147 / 255.0f, 112 / 255.0f, 219 / 255.0f, 1), "Pet: ");
						ImGui::SameLine(0.0f, 1.0f); ImGui::TextColored(ImVec4(147 / 255.0f, 112 / 255.0f, 219 / 255.0f, 1), Pets[playerI->fields.IKJHHHFMAIJ].c_str());
						ImGui::TextColored(ImVec4(147 / 255.0f, 112 / 255.0f, 219 / 255.0f, 1), "Skin: ");
						ImGui::SameLine(0.0f, 1.0f); ImGui::TextColored(ImVec4(147 / 255.0f, 112 / 255.0f, 219 / 255.0f, 1), Skins[playerI->fields.PJBKAJGBPAD].c_str());
						ImGui::TextColored(ImVec4(147 / 255.0f, 112 / 255.0f, 219 / 255.0f, 1), "Color: ");
						ImGui::SameLine(0.0f, 1.0f); ImGui::TextColored(ImVec4(147 / 255.0f, 112 / 255.0f, 219 / 255.0f, 1), Colors[playerI->fields.LHKAPPDILFP].c_str());
						if (ImGui::Button("Goto")) {
							CustomNetworkTransform_SnapTo(pControl->fields.NetTransform, PlayerControl_GetTruePosition(playerI->fields.OOGBDGNGIEM, NULL), NULL);
						}
						ImGui::SameLine(0.0f, 2.0f);
						if (ImGui::Button("Bring")) {
							CustomNetworkTransform_SnapTo(cnt, PlayerControl_GetTruePosition((PlayerControl__TypeInfo)->static_fields->LocalPlayer, NULL), NULL);
						}
						ImGui::SameLine(0.0f, 2.0f);
						if (ImGui::Button("Voided")) {
							CustomNetworkTransform_SnapTo(cnt, Vector2{ 9999999,9999999 }, NULL);
						}
						if (ImGui::Button("Force Meeting")) {
							PlayerControl_CmdReportDeadBody(playerI->fields.OOGBDGNGIEM, playerI, NULL);
						}
						if (ImGui::Button("Kick")) {
							kick(playerI->fields.OOGBDGNGIEM);
						}
					}
				}
			}
		}
	}
}

LRESULT CALLBACK WndProcHook(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	ImGuiIO& io = ImGui::GetIO();
	POINT mPos;
	GetCursorPos(&mPos);
	ScreenToClient(Window, &mPos);

	ImGui::GetIO().MousePos.x = mPos.x;
	ImGui::GetIO().MousePos.y = mPos.y;

	if (uMsg == WM_KEYUP && wParam == VK_INSERT)
		menu = !menu;

	if (menu)
		ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam);

	return CallWindowProcW(WndProcFunc, hWnd, uMsg, wParam, lParam);
}

HRESULT __stdcall D3D_FUNCTION_HOOK(IDXGISwapChain* pThis, UINT SyncInterval, UINT Flags)
{
	if (!ImGuiInit)
	{
		SwapChain = pThis;
		pThis->GetDevice(__uuidof(ID3D11Device), (void**)&Device);
		Device->GetImmediateContext(&Ctx);

		DXGI_SWAP_CHAIN_DESC desc;

		pThis->GetDesc(&desc);

		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;

		ImGui::StyleColorsDark();

		Window = desc.OutputWindow;

		ImGui_ImplWin32_Init(Window);
		ImGui_ImplDX11_Init(Device, Ctx);

		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

		WndProcFunc = (WNDPROC)SetWindowLongW(Window, GWLP_WNDPROC, (LONG)WndProcHook);

		ImGui::GetIO().ImeWindowHandle = Window;

		ID3D11Texture2D* pBackBuffer;
		pThis->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
		Device->CreateRenderTargetView(pBackBuffer, NULL, &RenderTargetView);
		pBackBuffer->Release();

		ImGui::GetStyle().WindowRounding = 0.0F;
		ImGui::GetStyle().ChildRounding = 0.0F;
		ImGui::GetStyle().FrameRounding = 0.0F;
		ImGui::GetStyle().GrabRounding = 0.0F;
		ImGui::GetStyle().PopupRounding = 0.0F;
		ImGui::GetStyle().ScrollbarRounding = 0.0F;

		ImGuiInit = true;
	}
	// get local stuff
	if ((PlayerControl__TypeInfo)->static_fields->LocalPlayer != nullptr)
		pControl = (PlayerControl*)((BYTE*)(PlayerControl__TypeInfo)->static_fields->LocalPlayer - 0x4); // they seem to be 4 byte off?
	if (pControl != nullptr) {
		if (pControl->fields.FMDMBBNEAHH != nullptr)
			pInfo = (PlayerInfo*)((BYTE*)pControl->fields.FMDMBBNEAHH); // they seem to be 4 byte off?
	}
	if (pControl != nullptr) {
		if (pControl->fields.MyPhysics != nullptr)
			pPhysics = (PlayerPhysics*)((BYTE*)pControl->fields.MyPhysics - 0x4); // they seem to be 4 byte off?
	}
	if (pControl != nullptr) {
		if (pControl->fields.NetTransform != nullptr)
			pCNT = (CustomNetworkTransform*)((BYTE*)pControl->fields.NetTransform - 0x4); // they seem to be 4 byte off?
	}
	if ((PlayerControl__TypeInfo)->static_fields->GameOptions != nullptr) {
		gameOptions = (PlayerControl__TypeInfo)->static_fields->GameOptions;
	}

	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	if (firstGo && pControl != nullptr) {
		output.info(concate(false, "[PlayerControl]-->", hexify(reinterpret_cast<UINT32>(pControl)).c_str()).c_str());
		output.info(concate(false, "[PlayerPhysics]-->", hexify(reinterpret_cast<UINT32>(pPhysics)).c_str()).c_str());
		output.info(concate(false, "[PlayerInfo]-->", hexify(reinterpret_cast<UINT32>(pInfo)).c_str()).c_str());
		output.info(concate(false, "[CustomNetworkTransform]-->", hexify(reinterpret_cast<UINT32>(pCNT)).c_str()).c_str());
		output.info(concate(false, "[GameOptions]-->", hexify(reinterpret_cast<UINT32>(gameOptions)).c_str()).c_str());
		firstGo = false;
	}
	if (zero)
		pControl->fields.killTimer = 0;

	if (pControl != nullptr && logData) {
		logGarbage();
	}
	if (spamMeet)
		breakServer();
	if (map) {
		if (ship != nullptr) {
			if (getAllVents(ship) == 14) {
				skeld();
			}
			else if (getAllVents(ship) == 12) {
				polus();
			}
			else if (getAllVents(ship) == 11) {
				hq();
			}
			//if (ship->fields.InitialSpawnCenter.x == 2.20);
		}
	}
	if (menu)
	{
		ImGui::PushStyleColor(ImGuiCol_TitleBg, ImVec4(147 / 255.0f, 112 / 255.0f, 219 / 255.0f, 1));
		ImGui::PushStyleColor(ImGuiCol_TitleBgActive, ImVec4(147 / 255.0f, 112 / 255.0f, 219 / 255.0f, 1));
		ImGui::PushStyleColor(ImGuiCol_TitleBgCollapsed, ImVec4(147 / 255.0f, 112 / 255.0f, 219 / 255.0f, 1));
		ImGui::SetWindowSize(ImVec2(400, 400));
		ImGui::Begin("Void Menu", &menu);
		ImGui::PopStyleColor(3);
		if (ImGui::Button("Self")) {
			tab = 0;
		}
		ImGui::SameLine(0.0f, 2.0f);
		if (ImGui::Button("Players")) {
			tab = 1;
		}
		ImGui::SameLine(0.0f, 2.0f);
		if (ImGui::Button("Ship")) {
			tab = 2;
		}
		ImGui::SameLine(0.0f, 2.0f);
		if (ImGui::Button("Settings")) {
			tab = 3;
		}
		ImGui::Separator();
		switch (tab) {
		case 0:
			if (pControl != nullptr || pPhysics != nullptr) {
				pid = pControl->fields.PlayerId;
				killTimer = pControl->fields.killTimer;
				if (pPhysics != nullptr)
					speed = pPhysics->fields.Speed;
				reportdist = pControl->fields.MaxReportDistance;
				remainingem = pControl->fields.RemainingEmergencies;
				if (gameOptions != nullptr) {
					speedmult = gameOptions->fields.DAJDLEBMBMB;
					lightradius = gameOptions->fields.LNKCMDOCNBI;
				}
				if (PlayerControl_get_Data(PlayerControl__TypeInfo->static_fields->LocalPlayer, NULL) != nullptr) {
					hat = PlayerControl_get_Data(PlayerControl__TypeInfo->static_fields->LocalPlayer, NULL)->fields.LJNAHAIMDOC;
					skin = PlayerControl_get_Data(PlayerControl__TypeInfo->static_fields->LocalPlayer, NULL)->fields.PJBKAJGBPAD;
					pet = PlayerControl_get_Data(PlayerControl__TypeInfo->static_fields->LocalPlayer, NULL)->fields.IKJHHHFMAIJ;
					color = PlayerControl_get_Data(PlayerControl__TypeInfo->static_fields->LocalPlayer, NULL)->fields.LHKAPPDILFP;
				}
				if (ImGui::SliderFloat("Kill Timer", &killTimer, 0, 25)) {
					if (killTimer == 0) {
						zero = true;
					}
					else {
						zero = false;
					}
					pControl->fields.killTimer = killTimer;
				}
				if (ImGui::SliderFloat("Speed", &speed, 0, 25)) {
					if (pPhysics != nullptr)
						pPhysics->fields.Speed = speed;
				}
				if (ImGui::SliderFloat("Report Distance", &reportdist, 0, 1000)) {
					pControl->fields.MaxReportDistance = reportdist;
				}
				if (ImGui::SliderInt("Emergencies", &remainingem, 0, 25)) {
					pControl->fields.RemainingEmergencies = remainingem;
				}
				if (ImGui::SliderInt(Hats[hat].c_str(), &hat, 0, 93)) {
					PlayerControl_RpcSetHat(PlayerControl__TypeInfo->static_fields->LocalPlayer, (uint32_t)hat, NULL);
				}
				if (ImGui::SliderInt(Pets[pet].c_str(), &pet, 0, 10)) {
					PlayerControl_RpcSetPet(PlayerControl__TypeInfo->static_fields->LocalPlayer, (uint32_t)pet, NULL);
				}
				if (ImGui::SliderInt(Skins[skin].c_str(), &skin, 0, 15)) {
					PlayerControl_RpcSetSkin(PlayerControl__TypeInfo->static_fields->LocalPlayer, (uint32_t)skin, NULL);
				}
				if (ImGui::SliderInt(Colors[color].c_str(), &color, 0, 11)) {
					PlayerControl_RpcSetColor(PlayerControl__TypeInfo->static_fields->LocalPlayer, (uint8_t)color, NULL);
					PlayerControl_get_Data(PlayerControl__TypeInfo->static_fields->LocalPlayer, NULL)->fields.LHKAPPDILFP = (uint8_t)color;
				}
				if (ImGui::Checkbox("Noclip", &noclip)) {
					if (noclip) {
						if ((PlayerControl__TypeInfo)->static_fields->LocalPlayer != nullptr || Component_get_gameObject((Component*)(PlayerControl__TypeInfo)->static_fields->LocalPlayer, NULL) != nullptr)
							GameObject_set_layer(Component_get_gameObject((Component*)(PlayerControl__TypeInfo)->static_fields->LocalPlayer, NULL), LayerMask_NameToLayer(netString("Ghost"), NULL), NULL);
						else
							output.error("Localplayer is nullptr, join a game.");
					}
					else {
						if ((PlayerControl__TypeInfo)->static_fields->LocalPlayer != nullptr || Component_get_gameObject((Component*)(PlayerControl__TypeInfo)->static_fields->LocalPlayer, NULL) != nullptr)
							GameObject_set_layer(Component_get_gameObject((Component*)(PlayerControl__TypeInfo)->static_fields->LocalPlayer, NULL), 8, NULL);
						else
							output.error("Localplayer is nullptr, join a game.");
					}
				}
				ImGui::SameLine(0.0f, 2.0f);
				if (ImGui::Checkbox("Danny Phantom", &ghostmode)) {
					if (ghostmode) {
						if ((PlayerControl__TypeInfo)->static_fields->LocalPlayer != nullptr || PlayerControl_get_Data(PlayerControl__TypeInfo->static_fields->LocalPlayer, NULL) != nullptr || Component_get_gameObject((Component*)(PlayerControl__TypeInfo)->static_fields->LocalPlayer, NULL) != nullptr) {
							GameObject_set_layer(Component_get_gameObject((Component*)(PlayerControl__TypeInfo)->static_fields->LocalPlayer, NULL), LayerMask_NameToLayer(netString("Ghost"), NULL), NULL);
							PlayerControl_get_Data(PlayerControl__TypeInfo->static_fields->LocalPlayer, NULL)->fields.DMFDFKEJHLH = true;
							output.info("Going ghost!");
						}
						else
							output.error("Localplayer is nullptr, join a game.");
					}
					else {
						if ((PlayerControl__TypeInfo)->static_fields->LocalPlayer != nullptr || PlayerControl_get_Data(PlayerControl__TypeInfo->static_fields->LocalPlayer, NULL) != nullptr || Component_get_gameObject((Component*)(PlayerControl__TypeInfo)->static_fields->LocalPlayer, NULL) != nullptr) {
							GameObject_set_layer(Component_get_gameObject((Component*)(PlayerControl__TypeInfo)->static_fields->LocalPlayer, NULL), 8, NULL);
							PlayerControl_get_Data(PlayerControl__TypeInfo->static_fields->LocalPlayer, NULL)->fields.DMFDFKEJHLH = false;
						}
						else
							output.error("Localplayer is nullptr, join a game.");
					}
				}
				if (ImGui::CollapsingHeader("Game Options")) {
					if (ImGui::SliderFloat("Speed Multiplier", &speedmult, 0, 10)) {
						if (gameOptions != nullptr)
							gameOptions->fields.DAJDLEBMBMB = speedmult;
						else
							output.error("GameOptions is nullptr, join a game.");
					}
					if (ImGui::SliderFloat("Light Radius", &lightradius, 0, 2.5f)) {
						if (gameOptions != nullptr) {
							gameOptions->fields.LNKCMDOCNBI = lightradius;
							gameOptions->fields.NFAOBDJKOPH = lightradius;
						}
						else {
							output.error("GameOptions is nullptr, join a game.");
						}
					}
				}
				if (ImGui::CollapsingHeader("Debug Options")) {
					if (ImGui::Button("Print X/Y")) {
						Vector2 p = PlayerControl_GetTruePosition(PlayerControl__TypeInfo->static_fields->LocalPlayer, NULL);
						output.info(concate(false, std::to_string(p.x).c_str(), ",", std::to_string(p.y).c_str()).c_str());
					}
				}
				break;
		case 1:
			ImGui::SliderInt("Player", &playerID, 0, 9);
			switch (playerID) {
			case 0:
				getPlayer(0);
				break;
			case 1:
				getPlayer(1);
				break;
			case 2:
				getPlayer(2);
				break;
			case 3:
				getPlayer(3);
				break;
			case 4:
				getPlayer(4);
				break;
			case 5:
				getPlayer(5);
				break;
			case 6:
				getPlayer(6);
				break;
			case 7:
				getPlayer(7);
				break;
			case 8:
				getPlayer(8);
				break;
			case 9:
				getPlayer(9);
				break;
			}
			break;
			}
			break;
		case 2:
			ImGui::Checkbox("Show Map", &map);
			ImGui::Separator();
			ImGui::Text("-- MAP SETTINGS --");
			ImGui::Checkbox("Show Ghosts", &showGhost);
			ImGui::Checkbox("Show Vents", &showVents);
			ImGui::Checkbox("Show Area Names", &showAreas);
			ImGui::SliderFloat("Map Alpha", &BACKGROUNDALPHA, 0.0f, 1.0f);
			ImGui::SliderFloat("Player Size", &playerSize, 1, 5);
			if (isDebug)
				if (ImGui::CollapsingHeader("MAP DEBUG SETTINGS")) {
					ImGui::SliderFloat("SPEED X", &SPEEDX, -10, 10);
					ImGui::SliderFloat("X", &X, -500, 500);
					ImGui::SliderFloat("SCALE X", &SCALEX, -10, 10);
					ImGui::SliderFloat("SPEED Y", &SPEEDY, -10, 10);
					ImGui::SliderFloat("Y", &Y, -500, 500);
					ImGui::SliderFloat("SCALE Y", &SCALEY, -10, 10);
					if (ship != nullptr)
						ImGui::Text(concate(false,"Vents: ",std::to_string(getAllVents(ship)).c_str()).c_str());
				}
			break;
		case 3:
			ImGui::Checkbox("Log game data", &logData);
			ImGui::Checkbox("Map Debugging", &isDebug);
			if (ImGui::Checkbox("Break Server", &spamMeet)) {
				if (spamMeet)
					output.info("Game will be in a constant loop of voting\nand sometimes freeze around the meeting area.");
			}
			break;
		}
		ImGui::Separator();
		output.draw();
		ImGui::End();
	}
	ImGui::EndFrame();
	ImGui::Render();

	Ctx->OMSetRenderTargets(1, &RenderTargetView, NULL);

	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

	return D3DPresentFunc(pThis, SyncInterval, Flags);
}

void hudHook(KeyboardJoystick* kJ, MethodInfo* m)
{
	KeyboardJoystickFunc(kJ, m);
}

void voteHook(VoteBanSystem* voteBS, MethodInfo* m) {
	if (voteban == nullptr)
		output.info(concate(false, "[VoteBanSystem]-->", hexify(reinterpret_cast<UINT32>(voteBS)).c_str()).c_str());
	voteban = voteBS;
	VoteBanSystemFunc(voteBS, m);
}

bool HookFunction(PVOID* original, PVOID detour) {
	LONG err = DetourAttach(original, detour);
	if (err != 0)
		return false;
	else
		return true;
}

void camHook(Camera* cam, MethodInfo* m) {
	if (camera == nullptr)
		output.info(concate(false, "[Camera]-->", hexify(reinterpret_cast<UINT32>(cam)).c_str()).c_str());
	camera = cam;
	CameraFireFunc(cam, m);
}

void shipHook(ShipStatus* s, MethodInfo* m) {
	if (ship == nullptr)
		output.info(concate(false, "[ShipStatus]-->", hexify(reinterpret_cast<UINT32>(s)).c_str()).c_str());
	ship = s;
	ShipStatusFunc(s, m);
}

void Run()
{
	KeyboardJoystickFunc = KeyboardJoystick_AGFODCIDMAK;
	D3DPresentFunc = GetD3D11PresentFunction();
	VoteBanSystemFunc = VoteBanSystem_Awake;
	CameraFireFunc = Camera_FireOnPostRender;
	ShipStatusFunc = ShipStatus_FixedUpdate;

	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());

	if (!HookFunction(&(PVOID&)VoteBanSystemFunc, voteHook))
		return;

	if (!HookFunction(&(PVOID&)CameraFireFunc, camHook))
		return;

	if (!HookFunction(&(PVOID&)KeyboardJoystickFunc, hudHook))
		return;


	if (!HookFunction(&(PVOID&)ShipStatusFunc, shipHook))
		return;

	if (D3DPresentFunc == NULL || !HookFunction(&(PVOID&)D3DPresentFunc, D3D_FUNCTION_HOOK))
		return;

	DetourTransactionCommit();
}