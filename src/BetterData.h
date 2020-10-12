#ifndef BETTERDATA_H
#define BETTERDATA_H

#include <string>
#include "il2cpp-appdata.h"
#include "imgui.h"
#include "imgui_impl_win32.h"
#include "imgui_impl_dx11.h"
#include "helpers.h"
#include <string>
#include <iostream>
#include <vector>
#include <set>
#include <locale>
#include <codecvt>
#include <queue>
#include <thread>
#include <algorithm>
#include <math.h>
#include <algorithm>
#include <cmath>
#include <iostream>

// these actually have no real use, just for memory
#define PLAYERINFO_ID 0x8
#define PLAYERINFO_COLOR 0x10
#define PLAYERINFO_HAT 0x14
#define PLAYERINFO_PET 0x18
#define PLAYERINFO_SKIN 0x1C
#define PLAYERINFO_DEAD 0x29
#define PLAYERINFO_IMPOSTER 0x28
#define PLAYERINFO_PLAYERCONTROL 0x2C
#define PLAYERINFO_VENTED 0x20
#define PLAYERCONTROL_KILLTIMER 0x44
#define PLAYERCONTROL_ID 0x28
#define PLAYERCONTROL_EMERGENCY 0x48
#define PLAYERCONTROL_CNT 0x60
#define PLAYERCONTROL_MAXREPORTDISTANCE 0x2C
#define PLAYERCONTROL_TEXTRENDER 0x4C
#define PLAYERPHYSYICS_SPEED 0x24
#define GAMEOPTIONS_SPEED_MULT 0x20

using namespace app;

Camera* camera = nullptr;
float SPEEDX = 9.157;
float X = 457.831;
float SCALEX = 0.482f;
float SPEEDY = -8.434;
float Y = 144.578;
float SCALEY = 0.482f;
float playerSize = 3;
bool showGhost = true;
bool showVents = true;
bool showAreas = true;
bool map = false;
bool isDebug = false;

void drawLine(ImDrawList* dl,ImVec2 p1, ImVec2 p2, ImVec4 color, float thick = 1.0f) {
	dl->AddLine(p1, p2, ImGui::ColorConvertFloat4ToU32(color), thick);
}

void drawRect(ImDrawList* dl, ImVec2 p1, ImVec2 p2, ImVec4 color) {
	dl->AddRectFilled(p1, p2, ImGui::ColorConvertFloat4ToU32(color));
}

void drawText(ImDrawList* dl, ImVec2 p, ImVec4 color, const char* text) {
	dl->AddText(p, ImGui::ColorConvertFloat4ToU32(color), text);
}

bool inGame() {
	return (AmongUsClient__TypeInfo)->static_fields->Instance->fields._.GameState == InnerNetClient_IFLBIJFJPMK__Enum_Joined || (AmongUsClient__TypeInfo)->static_fields->Instance->fields._.GameState == InnerNetClient_IFLBIJFJPMK__Enum_Started;
}

float BACKGROUNDALPHA = 1;

std::vector<PlayerControl*>getPlayers() {
	std::vector<PlayerControl*> players = std::vector<PlayerControl*>();
	for (int i = 0; i < List_1_PlayerControl__get_Count((PlayerControl__TypeInfo)->static_fields->AllPlayerControls, NULL); i++) {
		players.push_back(List_1_PlayerControl__get_Item((PlayerControl__TypeInfo)->static_fields->AllPlayerControls, i, NULL));
	}
	return players;
}

int getAllVents(ShipStatus* s) {
	if (s != nullptr) {
		return ShipStatus_get_AllVents(s, NULL)->max_length;
	}
}

void drawPlayers(ImDrawList* drawList, float radius) {
	if (getPlayers().size() > 0 && inGame) {
		for (auto p : getPlayers()) {
			if (p != nullptr) {
				if (p != PlayerControl__TypeInfo->static_fields->LocalPlayer) {
					Vector2 pos = PlayerControl_GetTruePosition(p, NULL);
					if (PlayerControl_get_Data(p, NULL)->fields.DMFDFKEJHLH != true) {
						if (PlayerControl_get_Data(p, NULL)->fields.LHKAPPDILFP == 0)
							drawList->AddCircleFilled({ (pos.x * SPEEDX) + X * SCALEX,(pos.y * SPEEDY) + Y * SCALEY }, radius, ImGui::ColorConvertFloat4ToU32({ 1,0,0,1 }));
						if (PlayerControl_get_Data(p, NULL)->fields.LHKAPPDILFP == 1)
							drawList->AddCircleFilled({ (pos.x * SPEEDX) + X * SCALEX,(pos.y * SPEEDY) + Y * SCALEY }, radius, ImGui::ColorConvertFloat4ToU32({ 0,0,1,1 }));
						if (PlayerControl_get_Data(p, NULL)->fields.LHKAPPDILFP == 2)
							drawList->AddCircleFilled({ (pos.x * SPEEDX) + X * SCALEX,(pos.y * SPEEDY) + Y * SCALEY }, radius, ImGui::ColorConvertFloat4ToU32({ 0,179 / 255.0f,0,1 }));
						if (PlayerControl_get_Data(p, NULL)->fields.LHKAPPDILFP == 3)
							drawList->AddCircleFilled({ (pos.x * SPEEDX) + X * SCALEX,(pos.y * SPEEDY) + Y * SCALEY }, radius, ImGui::ColorConvertFloat4ToU32({ 1,0,1,1 }));
						if (PlayerControl_get_Data(p, NULL)->fields.LHKAPPDILFP == 4)
							drawList->AddCircleFilled({ (pos.x * SPEEDX) + X * SCALEX,(pos.y * SPEEDY) + Y * SCALEY }, radius, ImGui::ColorConvertFloat4ToU32({ 1,165 / 255.0f,0,1 }));
						if (PlayerControl_get_Data(p, NULL)->fields.LHKAPPDILFP == 5)
							drawList->AddCircleFilled({ (pos.x * SPEEDX) + X * SCALEX,(pos.y * SPEEDY) + Y * SCALEY }, radius, ImGui::ColorConvertFloat4ToU32({ 1,1,102 / 255.0f,1 }));
						if (PlayerControl_get_Data(p, NULL)->fields.LHKAPPDILFP == 6)
							drawList->AddCircleFilled({ (pos.x * SPEEDX) + X * SCALEX,(pos.y * SPEEDY) + Y * SCALEY }, radius, ImGui::ColorConvertFloat4ToU32({ 0.25,0.25,0.25,1 }));
						if (PlayerControl_get_Data(p, NULL)->fields.LHKAPPDILFP == 7)
							drawList->AddCircleFilled({ (pos.x * SPEEDX) + X * SCALEX,(pos.y * SPEEDY) + Y * SCALEY }, radius, ImGui::ColorConvertFloat4ToU32({ 1,1,1,1 }));
						if (PlayerControl_get_Data(p, NULL)->fields.LHKAPPDILFP == 8)
							drawList->AddCircleFilled({ (pos.x * SPEEDX) + X * SCALEX,(pos.y * SPEEDY) + Y * SCALEY }, radius, ImGui::ColorConvertFloat4ToU32({ 138 / 255.0f,43 / 255.0f,226 / 255.0f,1 }));
						if (PlayerControl_get_Data(p, NULL)->fields.LHKAPPDILFP == 9)
							drawList->AddCircleFilled({ (pos.x * SPEEDX) + X * SCALEX,(pos.y * SPEEDY) + Y * SCALEY }, radius, ImGui::ColorConvertFloat4ToU32({ 139 / 255.0f,69 / 255.0f,19 / 255.0f,1 }));
						if (PlayerControl_get_Data(p, NULL)->fields.LHKAPPDILFP == 10)
							drawList->AddCircleFilled({ (pos.x * SPEEDX) + X * SCALEX,(pos.y * SPEEDY) + Y * SCALEY }, radius, ImGui::ColorConvertFloat4ToU32({ 0,1,1,1 }));
						if (PlayerControl_get_Data(p, NULL)->fields.LHKAPPDILFP == 11)
							drawList->AddCircleFilled({ (pos.x * SPEEDX) + X * SCALEX,(pos.y * SPEEDY) + Y * SCALEY }, radius, ImGui::ColorConvertFloat4ToU32({ 0,1,0,1 }));
					}
					else if (PlayerControl_get_Data(p, NULL)->fields.DMFDFKEJHLH && showGhost) {
						if (PlayerControl_get_Data(p, NULL)->fields.LHKAPPDILFP == 0)
							drawList->AddCircleFilled({ (pos.x * SPEEDX) + X * SCALEX,(pos.y * SPEEDY) + Y * SCALEY }, radius, ImGui::ColorConvertFloat4ToU32({ 1,0,0,0.3 }));
						if (PlayerControl_get_Data(p, NULL)->fields.LHKAPPDILFP == 1)
							drawList->AddCircleFilled({ (pos.x * SPEEDX) + X * SCALEX,(pos.y * SPEEDY) + Y * SCALEY }, radius, ImGui::ColorConvertFloat4ToU32({ 0,0,1,0.3 }));
						if (PlayerControl_get_Data(p, NULL)->fields.LHKAPPDILFP == 2)
							drawList->AddCircleFilled({ (pos.x * SPEEDX) + X * SCALEX,(pos.y * SPEEDY) + Y * SCALEY }, radius, ImGui::ColorConvertFloat4ToU32({ 0,179 / 255.0f,0,0.3 }));
						if (PlayerControl_get_Data(p, NULL)->fields.LHKAPPDILFP == 3)
							drawList->AddCircleFilled({ (pos.x * SPEEDX) + X * SCALEX,(pos.y * SPEEDY) + Y * SCALEY }, radius, ImGui::ColorConvertFloat4ToU32({ 1,0,1,0.3 }));
						if (PlayerControl_get_Data(p, NULL)->fields.LHKAPPDILFP == 4)
							drawList->AddCircleFilled({ (pos.x * SPEEDX) + X * SCALEX,(pos.y * SPEEDY) + Y * SCALEY }, radius, ImGui::ColorConvertFloat4ToU32({ 1,165 / 255.0f,0,0.3 }));
						if (PlayerControl_get_Data(p, NULL)->fields.LHKAPPDILFP == 5)
							drawList->AddCircleFilled({ (pos.x * SPEEDX) + X * SCALEX,(pos.y * SPEEDY) + Y * SCALEY }, radius, ImGui::ColorConvertFloat4ToU32({ 1,1,102 / 255.0f,0.3 }));
						if (PlayerControl_get_Data(p, NULL)->fields.LHKAPPDILFP == 6)
							drawList->AddCircleFilled({ (pos.x * SPEEDX) + X * SCALEX,(pos.y * SPEEDY) + Y * SCALEY }, radius, ImGui::ColorConvertFloat4ToU32({ 0.25,0.25,0.25,0.3 }));
						if (PlayerControl_get_Data(p, NULL)->fields.LHKAPPDILFP == 7)
							drawList->AddCircleFilled({ (pos.x * SPEEDX) + X * SCALEX,(pos.y * SPEEDY) + Y * SCALEY }, radius, ImGui::ColorConvertFloat4ToU32({ 1,1,1,0.3 }));
						if (PlayerControl_get_Data(p, NULL)->fields.LHKAPPDILFP == 8)
							drawList->AddCircleFilled({ (pos.x * SPEEDX) + X * SCALEX,(pos.y * SPEEDY) + Y * SCALEY }, radius, ImGui::ColorConvertFloat4ToU32({ 138 / 255.0f,43 / 255.0f,226 / 255.0f,0.3 }));
						if (PlayerControl_get_Data(p, NULL)->fields.LHKAPPDILFP == 9)
							drawList->AddCircleFilled({ (pos.x * SPEEDX) + X * SCALEX,(pos.y * SPEEDY) + Y * SCALEY }, radius, ImGui::ColorConvertFloat4ToU32({ 139 / 255.0f,69 / 255.0f,19 / 255.0f,0.3 }));
						if (PlayerControl_get_Data(p, NULL)->fields.LHKAPPDILFP == 10)
							drawList->AddCircleFilled({ (pos.x * SPEEDX) + X * SCALEX,(pos.y * SPEEDY) + Y * SCALEY }, radius, ImGui::ColorConvertFloat4ToU32({ 0,1,1,0.3 }));
						if (PlayerControl_get_Data(p, NULL)->fields.LHKAPPDILFP == 11)
							drawList->AddCircleFilled({ (pos.x * SPEEDX) + X * SCALEX,(pos.y * SPEEDY) + Y * SCALEY }, radius, ImGui::ColorConvertFloat4ToU32({ 0,1,0,0.3 }));
					}
				}
				else {
					Vector2 pos = PlayerControl_GetTruePosition(PlayerControl__TypeInfo->static_fields->LocalPlayer, NULL);
					if (PlayerControl_get_Data(PlayerControl__TypeInfo->static_fields->LocalPlayer, NULL)->fields.LHKAPPDILFP == 0)
						drawList->AddCircleFilled({ (pos.x * SPEEDX) + X * SCALEX,(pos.y * SPEEDY) + Y * SCALEY }, radius, ImGui::ColorConvertFloat4ToU32({ 1,0,0,1 }));
					if (PlayerControl_get_Data(PlayerControl__TypeInfo->static_fields->LocalPlayer, NULL)->fields.LHKAPPDILFP == 1)
						drawList->AddCircleFilled({ (pos.x * SPEEDX) + X * SCALEX,(pos.y * SPEEDY) + Y * SCALEY }, radius, ImGui::ColorConvertFloat4ToU32({ 0,0,1,1 }));
					if (PlayerControl_get_Data(PlayerControl__TypeInfo->static_fields->LocalPlayer, NULL)->fields.LHKAPPDILFP == 2)
						drawList->AddCircleFilled({ (pos.x * SPEEDX) + X * SCALEX,(pos.y * SPEEDY) + Y * SCALEY }, radius, ImGui::ColorConvertFloat4ToU32({ 0,179 / 255.0f,0,1 }));
					if (PlayerControl_get_Data(PlayerControl__TypeInfo->static_fields->LocalPlayer, NULL)->fields.LHKAPPDILFP == 3)
						drawList->AddCircleFilled({ (pos.x * SPEEDX) + X * SCALEX,(pos.y * SPEEDY) + Y * SCALEY }, radius, ImGui::ColorConvertFloat4ToU32({ 1,0,1,1 }));
					if (PlayerControl_get_Data(PlayerControl__TypeInfo->static_fields->LocalPlayer, NULL)->fields.LHKAPPDILFP == 4)
						drawList->AddCircleFilled({ (pos.x * SPEEDX) + X * SCALEX,(pos.y * SPEEDY) + Y * SCALEY }, radius, ImGui::ColorConvertFloat4ToU32({ 1,165 / 255.0f,0,1 }));
					if (PlayerControl_get_Data(PlayerControl__TypeInfo->static_fields->LocalPlayer, NULL)->fields.LHKAPPDILFP == 5)
						drawList->AddCircleFilled({ (pos.x * SPEEDX) + X * SCALEX,(pos.y * SPEEDY) + Y * SCALEY }, radius, ImGui::ColorConvertFloat4ToU32({ 1,1,102 / 255.0f,1 }));
					if (PlayerControl_get_Data(PlayerControl__TypeInfo->static_fields->LocalPlayer, NULL)->fields.LHKAPPDILFP == 6)
						drawList->AddCircleFilled({ (pos.x * SPEEDX) + X * SCALEX,(pos.y * SPEEDY) + Y * SCALEY }, radius, ImGui::ColorConvertFloat4ToU32({ 0.25,0.25,0.25,1 }));
					if (PlayerControl_get_Data(PlayerControl__TypeInfo->static_fields->LocalPlayer, NULL)->fields.LHKAPPDILFP == 7)
						drawList->AddCircleFilled({ (pos.x * SPEEDX) + X * SCALEX,(pos.y * SPEEDY) + Y * SCALEY }, radius, ImGui::ColorConvertFloat4ToU32({ 1,1,1,1 }));
					if (PlayerControl_get_Data(PlayerControl__TypeInfo->static_fields->LocalPlayer, NULL)->fields.LHKAPPDILFP == 8)
						drawList->AddCircleFilled({ (pos.x * SPEEDX) + X * SCALEX,(pos.y * SPEEDY) + Y * SCALEY }, radius, ImGui::ColorConvertFloat4ToU32({ 138 / 255.0f,43 / 255.0f,226 / 255.0f,1 }));
					if (PlayerControl_get_Data(PlayerControl__TypeInfo->static_fields->LocalPlayer, NULL)->fields.LHKAPPDILFP == 9)
						drawList->AddCircleFilled({ (pos.x * SPEEDX) + X * SCALEX,(pos.y * SPEEDY) + Y * SCALEY }, radius, ImGui::ColorConvertFloat4ToU32({ 139 / 255.0f,69 / 255.0f,19 / 255.0f,1 }));
					if (PlayerControl_get_Data(PlayerControl__TypeInfo->static_fields->LocalPlayer, NULL)->fields.LHKAPPDILFP == 10)
						drawList->AddCircleFilled({ (pos.x * SPEEDX) + X * SCALEX,(pos.y * SPEEDY) + Y * SCALEY }, radius, ImGui::ColorConvertFloat4ToU32({ 0,1,1,1 }));
					if (PlayerControl_get_Data(PlayerControl__TypeInfo->static_fields->LocalPlayer, NULL)->fields.LHKAPPDILFP == 11)
						drawList->AddCircleFilled({ (pos.x * SPEEDX) + X * SCALEX,(pos.y * SPEEDY) + Y * SCALEY }, radius, ImGui::ColorConvertFloat4ToU32({ 0,1,0,1 }));
				}
			}
		}
	}
}

void setMapSettings(float speedX, float X1, float scaleX, float speedY, float Y1, float scaleY) {
	SPEEDX = speedX;
	X = X1;
	SCALEX = scaleX;
	SPEEDY = speedY;
	Y = Y1;
	SCALEY = scaleY;
}

void hq() {
	if (!isDebug)
		setMapSettings(7.183, -21.127, -6.197f, -7.183, 345.070, 0.563f);
	ImDrawList* drawList = ImGui::GetBackgroundDrawList();
	drawRect(drawList, { 0,0 }, { 400,230 }, { 0,0,0,BACKGROUNDALPHA });
	drawLine(drawList, { 50,136 }, { 131,136 }, { 1,1,1,1 });
	drawLine(drawList, { 131,136 }, { 131,196 }, { 1,1,1,1 });
	drawLine(drawList, { 131,196}, { 113,196 }, { 1,1,1,1 });
	drawLine(drawList, { 88,196 }, { 50,196 }, { 1,1,1,1 });
	drawLine(drawList, { 50,196 }, { 50,136 }, { 1,1,1,1 });
	drawLine(drawList, { 113,196 }, { 113,201 }, { 1,1,1,1 });
	drawLine(drawList, { 113,201 }, { 159,201 }, { 1,1,1,1 });
	drawLine(drawList, { 159,201 }, { 159,195 }, { 1,1,1,1 });
	drawLine(drawList, { 159,195 }, { 159,175 }, { 1,1,1,1 });
	drawLine(drawList, { 159,195 }, { 212,195 }, { 1,1,1,1 });
	drawLine(drawList, { 159,175 }, { 167,175 }, { 1,1,1,1 });
	drawLine(drawList, { 212,195 }, { 212,171 }, { 1,1,1,1 });
	drawLine(drawList, { 167,175 }, { 167,125 }, { 1,1,1,1 });
	drawLine(drawList, { 167,125 }, { 132,125 }, { 1,1,1,1 });
	drawLine(drawList, { 132,125 }, { 132,74 }, { 1,1,1,1 });
	drawLine(drawList, { 132,74 }, { 167,74 }, { 1,1,1,1 });
	drawLine(drawList, { 167,74 }, { 167,116 }, { 1,1,1,1 });
	drawLine(drawList, { 167,84 }, { 219,84 }, { 1,1,1,1 });
	drawLine(drawList, { 219,84 }, { 219,125 }, { 1,1,1,1 });
	drawLine(drawList, { 219,125 }, { 184,125 }, { 1,1,1,1 });
	drawLine(drawList, { 184,84 }, { 184,89 }, { 1,1,1,1 });
	drawLine(drawList, { 184,98 }, { 184,175 }, { 1,1,1,1 });
	drawLine(drawList, { 184,175 }, { 191,175 }, { 1,1,1,1 });
	drawLine(drawList, { 191,175 }, { 191,151 }, { 1,1,1,1 });
	drawLine(drawList, { 191,151 }, { 212,151 }, { 1,1,1,1 });
	drawLine(drawList, { 212,151 }, { 212,163 }, { 1,1,1,1 });
	drawLine(drawList, { 212,151 }, { 212,134 }, { 1,1,1,1 });
	drawLine(drawList, { 212,134 }, { 223,134 }, { 1,1,1,1 });
	drawLine(drawList, { 223,134 }, { 250,106 }, { 1,1,1,1 });
	drawLine(drawList, { 250,106 }, { 250,74 }, { 1,1,1,1 });
	drawLine(drawList, { 250,74 }, { 223,74 }, { 1,1,1,1 });
	drawLine(drawList, { 223,74 }, { 223,37 }, { 1,1,1,1 });
	drawLine(drawList, { 229,151 }, { 229,163 }, { 1,1,1,1 });
	drawLine(drawList, { 223,37 }, { 223,7 }, { 1,1,1,1 });
	drawLine(drawList, { 223,37 }, { 255,37 }, { 1,1,1,1 });
	drawLine(drawList, { 250,37 }, { 250,66 }, { 1,1,1,1 });
	drawLine(drawList, { 223,28 }, { 233,19 }, { 1,1,1,1 });
	drawLine(drawList, { 233,19 }, { 246,10 }, { 1,1,1,1 });
	drawLine(drawList, { 246,10 }, { 259,9 }, { 1,1,1,1 });
	drawLine(drawList, { 260,9 }, { 273,11 }, { 1,1,1,1 });
	drawLine(drawList, { 273,11 }, { 285,20 }, { 1,1,1,1 });
	drawLine(drawList, { 285,20 }, { 295,29 }, { 1,1,1,1 });
	drawLine(drawList, { 295,7 }, { 295,74 }, { 1,1,1,1 });
	drawLine(drawList, { 295,74 }, { 267,74 }, { 1,1,1,1 });
	drawLine(drawList, { 295,37 }, { 263,37 }, { 1,1,1,1 });
	drawLine(drawList, { 267,37 }, { 267,55 }, { 1,1,1,1 });
	drawLine(drawList, { 267,63 }, { 267,106 }, { 1,1,1,1 });
	drawLine(drawList, { 267,106 }, { 295,134 }, { 1,1,1,1 });
	drawLine(drawList, { 295,134 }, { 306,134 }, { 1,1,1,1 });
	drawLine(drawList, { 306,134 }, { 306,151 }, { 1,1,1,1 });
	drawLine(drawList, { 289,151 }, { 259,120 }, { 1,1,1,1 });
	drawLine(drawList, { 259,120 }, { 229,151 }, { 1,1,1,1 });
	drawLine(drawList, { 229,151 }, { 254,151 }, { 1,1,1,1 });
	drawLine(drawList, { 254,151 }, { 254,212 }, { 1,1,1,1 });
	drawLine(drawList, { 254,212 }, { 159,212 }, { 1,1,1,1 });
	drawLine(drawList, { 254,179 }, { 229,179 }, { 1,1,1,1 });
	drawLine(drawList, { 229,191 }, { 229,171 }, { 1,1,1,1 });
	drawLine(drawList, { 229,199 }, { 229,212 }, { 1,1,1,1 });
	drawLine(drawList, { 159,212 }, { 159,216 }, { 1,1,1,1 });
	drawLine(drawList, { 159,216 }, { 88,216 }, { 1,1,1,1 });
	drawLine(drawList, { 88,216 }, { 88,196 }, { 1,1,1,1 });
	drawLine(drawList, { 259,151 }, { 289,151 }, { 1,1,1,1 });
	drawLine(drawList, { 282,151 }, { 282,185 }, { 1,1,1,1 });
	drawLine(drawList, { 282,185 }, { 275,185 }, { 1,1,1,1 });
	drawLine(drawList, { 259,151 }, { 259,224 }, { 1,1,1,1 });
	drawLine(drawList, { 259,185 }, { 267,185 }, { 1,1,1,1 });
	drawLine(drawList, { 259,200 }, { 280,200 }, { 1,1,1,1 });
	drawLine(drawList, { 277,224 }, { 277,216 }, { 1,1,1,1 });
	drawLine(drawList, { 259,224 }, { 277,224 }, { 1,1,1,1 });
	drawLine(drawList, { 297,200 }, { 305,200 }, { 1,1,1,1 });
	drawLine(drawList, { 277,216 }, { 340,216 }, { 1,1,1,1 });
	drawLine(drawList, { 340,216 }, { 340,151 }, { 1,1,1,1 });
	drawLine(drawList, { 340,151 }, { 306,151 }, { 1,1,1,1 });
	drawLine(drawList, { 340,200 }, { 323,200 }, { 1,1,1,1 });
	if (showAreas) {
		drawText(drawList, { 60,150 }, { 1,1,1,1 }, "Launchpad");
		drawText(drawList, { 135,78 }, { 1,1,1,1 }, "Reac.");
		drawText(drawList, { 192,89 }, { 1,1,1,1 }, "Lab");
		drawText(drawList, { 195,155 }, { 1,1,1,1 }, "LR");
		drawText(drawList, { 233,186 }, { 1,1,1,1 }, "Med");
		drawText(drawList, { 232,156 }, { 1,1,1,1 }, "Com"); // this map sucks
		drawText(drawList, { 263,156 }, { 1,1,1,1 }, "Str");
		drawText(drawList, { 280,202 }, { 1,1,1,1 }, "Balcony");
		drawText(drawList, { 295,173 }, { 1,1,1,1 }, "Cafe");
		drawText(drawList, { 226,40 }, { 1,1,1,1 }, "Off.");
		drawText(drawList, { 270,42 }, { 1,1,1,1 }, "Adm.");
		drawText(drawList, { 245,17 }, { 1,1,1,1 }, "G.H");
	}
	if (showVents) {
		drawRect(drawList, { 299,204 }, { 302,206 }, { 1,0,0,1 });
		drawRect(drawList, { 300,140 }, { 303,138 }, { 1,0,0,1 });
		drawRect(drawList, { 289,71 }, { 292,69 }, { 1,0,0,1 });
		drawRect(drawList, { 258,14 }, { 261,12 }, { 1,0,0,1 });
		drawRect(drawList, { 226,49 }, { 229,47 }, { 1,0,0,1 });
		drawRect(drawList, { 212,98 }, { 215,96 }, { 1,0,0,1 });
		drawRect(drawList, { 135,122 }, { 138,120 }, { 1,0,0,1 });
		drawRect(drawList, { 178,170 }, { 181,172 }, { 1,0,0,1 });
		drawRect(drawList, { 162,192 }, { 165,190 }, { 1,0,0,1 });
		drawRect(drawList, { 240,209 }, { 243,207 }, { 1,0,0,1 });
		drawRect(drawList, { 86,168 }, { 89,170 }, { 1,0,0,1 });
	}

	drawPlayers(drawList, playerSize);
}

void polus() {
	if(!isDebug)
		setMapSettings(7.778, 225.490, 0.196f, -7.516, 310.458, 0.065f);
	ImDrawList* drawList = ImGui::GetBackgroundDrawList();
	drawRect(drawList, { 0,0 }, { 400,230 }, { 0,0,0,BACKGROUNDALPHA });
	drawLine(drawList, { 45,215 }, { 79,215 }, { 1,1,1,1 });
	drawLine(drawList, { 79,215 }, { 79,194 }, { 1,1,1,1 });
	drawLine(drawList, { 79,194 }, { 77,194 }, { 1,1,1,1 });
	drawLine(drawList, { 79,194 }, { 79,191 }, { 1,1,1,1 });
	drawLine(drawList, { 79,191 }, { 85,191 }, { 1,1,1,1 });
	drawLine(drawList, { 96,191 }, { 98,191 }, { 1,1,1,1 });
	drawLine(drawList, { 98,191}, { 98,160 }, { 1,1,1,1 });
	drawLine(drawList, { 98,160 }, { 94,160 }, { 1,1,1,1 });
	drawLine(drawList, { 94,160 }, { 92,160 }, { 1,1,1,1 });
	drawLine(drawList, { 94,160 }, { 94,126 }, { 1,1,1,1 });
	drawLine(drawList, { 94,126 }, { 132,126 }, { 1,1,1,1 });
	drawLine(drawList, { 132,126 }, { 132,100 }, { 1,1,1,1 });
	drawLine(drawList, { 132,100 }, { 132,98 }, { 1,1,1,1 });
	drawLine(drawList, { 132,100 }, { 108,100 }, { 1,1,1,1 });
	drawLine(drawList, { 98,100 }, { 96,100 }, { 1,1,1,1 });
	drawLine(drawList, { 96,100 }, { 96,120 }, { 1,1,1,1 });
	drawLine(drawList, { 96,120 }, { 94,120 }, { 1,1,1,1 });
	drawLine(drawList, { 94,120 }, { 94,126 }, { 1,1,1,1 });
	drawLine(drawList, { 94,120 }, { 93,120 }, { 1,1,1,1 });
	drawLine(drawList, { 81,120 }, { 79,120 }, { 1,1,1,1 });
	drawLine(drawList, { 79,120 }, { 79,160 }, { 1,1,1,1 });
	drawLine(drawList, { 75,160 }, { 81,160 }, { 1,1,1,1 });
	drawLine(drawList, { 77,160 }, { 77,139 }, { 1,1,1,1 });
	drawLine(drawList, { 77,139 }, { 69,131 }, { 1,1,1,1 });
	drawLine(drawList, { 69,131 }, { 45,131 }, { 1,1,1,1 });
	drawLine(drawList, { 45,131 }, { 45,160 }, { 1,1,1,1 });
	drawLine(drawList, { 45,160 }, { 63,160 }, { 1,1,1,1 });
	drawLine(drawList, { 63,160 }, { 63,181 }, { 1,1,1,1 });
	drawLine(drawList, { 63,181 }, { 61,181 }, { 1,1,1,1 });
	drawLine(drawList, { 50,181 }, { 45,181 }, { 1,1,1,1 });
	drawLine(drawList, { 45,160 }, { 45,194 }, { 1,1,1,1 });
	drawLine(drawList, { 45,194 }, { 65,194 }, { 1,1,1,1 });
	drawLine(drawList, { 45,194 }, { 45,215 }, { 1,1,1,1 });
	drawLine(drawList, { 45,215 }, { 79,215 }, { 1,1,1,1 });
	drawLine(drawList, { 79,120 }, { 79,100 }, { 1,1,1,1 });
	drawLine(drawList, { 79,100 }, { 70,100 }, { 1,1,1,1 });
	drawLine(drawList, { 59,100 }, { 56,100 }, { 1,1,1,1 });
	drawLine(drawList, { 56,100 }, { 56,120 }, { 1,1,1,1 });
	drawLine(drawList, { 56,120 }, { 79,120 }, { 1,1,1,1 });
	drawLine(drawList, { 56,100 }, { 56,81 }, { 1,1,1,1 });
	drawLine(drawList, { 56,81 }, { 132,81 }, { 1,1,1,1 });
	drawLine(drawList, { 132,81 }, { 132,85 }, { 1,1,1,1 });
	drawLine(drawList, { 120,216 }, { 120,189 }, { 1,1,1,1 });
	drawLine(drawList, { 120,189 }, { 141,189 }, { 1,1,1,1 });
	drawLine(drawList, { 141,189 }, { 141,178 }, { 1,1,1,1 });
	drawLine(drawList, { 153,178 }, { 153,189 }, { 1,1,1,1 });
	drawLine(drawList, { 153,189 }, { 156,189 }, { 1,1,1,1 });
	drawLine(drawList, { 156,189 }, { 156,206 }, { 1,1,1,1 });
	drawLine(drawList, { 156,206 }, { 146,216 }, { 1,1,1,1 });
	drawLine(drawList, { 145,216 }, { 120,216 }, { 1,1,1,1 });
	drawLine(drawList, { 123,171 }, { 123,136 }, { 1,1,1,1 });
	drawLine(drawList, { 123,136 }, { 147,136 }, { 1,1,1,1 });
	drawLine(drawList, { 147,136 }, { 147,158 }, { 1,1,1,1 });
	drawLine(drawList, { 147,158 }, { 135,158 }, { 1,1,1,1 });
	drawLine(drawList, { 135,158 }, { 135,171 }, { 1,1,1,1 });
	drawLine(drawList, { 179,98 }, { 222,98 }, { 1,1,1,1 });
	drawLine(drawList, { 222,98 }, { 222,120 }, { 1,1,1,1 });
	drawLine(drawList, { 222,120 }, { 189,120 }, { 1,1,1,1 });
	drawLine(drawList, { 189,120 }, { 189,110 }, { 1,1,1,1 });
	drawLine(drawList, { 189,110 }, { 179,110 }, { 1,1,1,1 });
	drawLine(drawList, { 76,77 }, { 76,56 }, { 1,1,1,1 });
	drawLine(drawList, { 76,56 }, { 73,53 }, { 1,1,1,1 });
	drawLine(drawList, { 73,53 }, { 73,48 }, { 1,1,1,1 });
	drawLine(drawList, { 73,48 }, { 76,45 }, { 1,1,1,1 });
	drawLine(drawList, { 76,45 }, { 82,45 }, { 1,1,1,1 });
	drawLine(drawList, { 82,45 }, { 85,50 }, { 1,1,1,1 });
	drawLine(drawList, { 85,50 }, { 84,53 }, { 1,1,1,1 });
	drawLine(drawList, { 84,53 }, { 81,56 }, { 1,1,1,1 });
	drawLine(drawList, { 81,56 }, { 81,77 }, { 1,1,1,1 });
	drawLine(drawList, { 230,70 }, { 230,49 }, { 1,1,1,1 });
	drawLine(drawList, { 230,49 }, { 227,46 }, { 1,1,1,1 });
	drawLine(drawList, { 227,46 }, { 227,41 }, { 1,1,1,1 });
	drawLine(drawList, { 227,41 }, { 231,37 }, { 1,1,1,1 });
	drawLine(drawList, { 231,37 }, { 234,37 }, { 1,1,1,1 });
	drawLine(drawList, { 234,37 }, { 238,41 }, { 1,1,1,1 });
	drawLine(drawList, { 238,41 }, { 238,46 }, { 1,1,1,1 });
	drawLine(drawList, { 238,46 }, { 235,49 }, { 1,1,1,1 });
	drawLine(drawList, { 235,49 }, { 235,70 }, { 1,1,1,1 });
	drawLine(drawList, { 155,85 }, { 194,85 }, { 1,1,1,1 });
	drawLine(drawList, { 194,85 }, { 192,74 }, { 1,1,1,1 });
	drawLine(drawList, { 192,74 }, { 198,66 }, { 1,1,1,1 });
	drawLine(drawList, { 198,66 }, { 198,57 }, { 1,1,1,1 });
	drawLine(drawList, { 198,57 }, { 200,57 }, { 1,1,1,1 });
	drawLine(drawList, { 200,57 }, { 200,68 }, { 1,1,1,1 });
	drawLine(drawList, { 200,68 }, { 213,71 }, { 1,1,1,1 });
	drawLine(drawList, { 213,71 }, { 216,59 }, { 1,1,1,1 });
	drawLine(drawList, { 216,59 }, { 216,43 }, { 1,1,1,1 });
	drawLine(drawList, { 216,43 }, { 204,40 }, { 1,1,1,1 });
	drawLine(drawList, { 204,40 }, { 202,48 }, { 1,1,1,1 });
	drawLine(drawList, { 202,48 }, { 198,48 }, { 1,1,1,1 });
	drawLine(drawList, { 198,48 }, { 198,16 }, { 1,1,1,1 });
	drawLine(drawList, { 198,16 }, { 194,10 }, { 1,1,1,1 });
	drawLine(drawList, { 194,10 }, { 185,5 }, { 1,1,1,1 });
	drawLine(drawList, { 185,5 }, { 164,5 }, { 1,1,1,1 });
	drawLine(drawList, { 164,5 }, { 151,14 }, { 1,1,1,1 });
	drawLine(drawList, { 151,14 }, { 151,48 }, { 1,1,1,1 });
	drawLine(drawList, { 151,48 }, { 146,48 }, { 1,1,1,1 });
	drawLine(drawList, { 146,48 }, { 145,41 }, { 1,1,1,1 });
	drawLine(drawList, { 145,41 }, { 132,43 }, { 1,1,1,1 });
	drawLine(drawList, { 132,43 }, { 132,56 }, { 1,1,1,1 });
	drawLine(drawList, { 132,56 }, { 136,71 }, { 1,1,1,1 });
	drawLine(drawList, { 136,71 }, { 148,68 }, { 1,1,1,1 });
	drawLine(drawList, { 148,68 }, { 148,58 }, { 1,1,1,1 });
	drawLine(drawList, { 148,58 }, { 151,56 }, { 1,1,1,1 });
	drawLine(drawList, { 151,56 }, { 151,67 }, { 1,1,1,1 });
	drawLine(drawList, { 151,67 }, { 156,73 }, { 1,1,1,1 });
	drawLine(drawList, { 156,73 }, { 155,85 }, { 1,1,1,1 });
	drawLine(drawList, { 156,73 }, { 157,70 }, { 1,1,1,1 });
	drawLine(drawList, { 157,70 }, { 191,70 }, { 1,1,1,1 });
	drawLine(drawList, { 191,70 }, { 192,74 }, { 1,1,1,1 });
	drawLine(drawList, { 156,73 }, { 156,49 }, { 1,1,1,1 });
	drawLine(drawList, { 156,49 }, { 155,49 }, { 1,1,1,1 });
	drawLine(drawList, { 154,48 }, { 155,48 }, { 1,1,1,1 });
	drawLine(drawList, { 154,48 }, { 154,17 }, { 1,1,1,1 });
	drawLine(drawList, { 154,48 }, { 154,17 }, { 1,1,1,1 });
	drawLine(drawList, { 154,48 }, { 154,17 }, { 1,1,1,1 });
	drawLine(drawList, { 154,17 }, { 167,12 }, { 1,1,1,1 });
	drawLine(drawList, { 167,12 }, { 181,12 }, { 1,1,1,1 });
	drawLine(drawList, { 181,12 }, { 194,17 }, { 1,1,1,1 });
	drawLine(drawList, { 194,17 }, { 194,48 }, { 1,1,1,1 });
	drawLine(drawList, { 194,48 }, { 193,48 }, { 1,1,1,1 });
	drawLine(drawList, { 192,49 }, { 193,49 }, { 1,1,1,1 });
	drawLine(drawList, { 192,49 }, { 192,74 }, { 1,1,1,1 });
	drawLine(drawList, { 167,140 }, { 167,160 }, { 1,1,1,1 });
	drawLine(drawList, { 167,160 }, { 173,160 }, { 1,1,1,1 });
	drawLine(drawList, { 167,160 }, { 167,174 }, { 1,1,1,1 });
	drawLine(drawList, { 167,174 }, { 183,174 }, { 1,1,1,1 });
	drawLine(drawList, { 179,174 }, { 179,182 }, { 1,1,1,1 });
	drawLine(drawList, { 179,194 }, { 179,198 }, { 1,1,1,1 });
	drawLine(drawList, { 179,198 }, { 196,198 }, { 1,1,1,1 });
	drawLine(drawList, { 194,174 }, { 202,174 }, { 1,1,1,1 });
	drawLine(drawList, { 196,174 }, { 196,220 }, { 1,1,1,1 });
	drawLine(drawList, { 196,220 }, { 222,220 }, { 1,1,1,1 });
	drawLine(drawList, { 222,220 }, { 222,200 }, { 1,1,1,1 });
	drawLine(drawList, { 222,200 }, { 226,200 }, { 1,1,1,1 });
	drawLine(drawList, { 222,220 }, { 243,220 }, { 1,1,1,1 });
	drawLine(drawList, { 243,220 }, { 243,216 }, { 1,1,1,1 });
	drawLine(drawList, { 235,200 }, { 243,200 }, { 1,1,1,1 });
	drawLine(drawList, { 243,202 }, { 243,160 }, { 1,1,1,1 });
	drawLine(drawList, { 213,174 }, { 243,174 }, { 1,1,1,1 });
	drawLine(drawList, { 240,160 }, { 268,160 }, { 1,1,1,1 });
	drawLine(drawList, { 268,160 }, { 268,158 }, { 1,1,1,1 });
	drawLine(drawList, { 268,145 }, { 268,140 }, { 1,1,1,1 });
	drawLine(drawList, { 268,140 }, { 167,140 }, { 1,1,1,1 });
	drawLine(drawList, { 227,140 }, { 227,160 }, { 1,1,1,1 });
	drawLine(drawList, { 223,160 }, { 229,160 }, { 1,1,1,1 });
	drawLine(drawList, { 184,160 }, { 212,160 }, { 1,1,1,1 });
	drawLine(drawList, { 243,216 }, { 268,216 }, { 1,1,1,1 });
	drawLine(drawList, { 268,216 }, { 268,184 }, { 1,1,1,1 });
	drawLine(drawList, { 268,184 }, { 306,184 }, { 1,1,1,1 });
	drawLine(drawList, { 306,172 }, { 254,172 }, { 1,1,1,1 });
	drawLine(drawList, { 254,172 }, { 254,202 }, { 1,1,1,1 });
	drawLine(drawList, { 254,202 }, { 243,202 }, { 1,1,1,1 });
	drawLine(drawList, { 306,172 }, { 306,170 }, { 1,1,1,1 });
	drawLine(drawList, { 306,170 }, { 316,160 }, { 1,1,1,1 });
	drawLine(drawList, { 316,160 }, { 342,160 }, { 1,1,1,1 });
	drawLine(drawList, { 342,106 }, { 342,161 }, { 1,1,1,1 });
	drawLine(drawList, { 306,184 }, { 316,195 }, { 1,1,1,1 });
	drawLine(drawList, { 316,195 }, { 342,195 }, { 1,1,1,1 });
	drawLine(drawList, { 342,195 }, { 351,186 }, { 1,1,1,1 });
	drawLine(drawList, { 351,186 }, { 351,169 }, { 1,1,1,1 });
	drawLine(drawList, { 351,169 }, { 356,163 }, { 1,1,1,1 });
	drawLine(drawList, { 356,163 }, { 356,106 }, { 1,1,1,1 });
	drawLine(drawList, { 356,106 }, { 366,106 }, { 1,1,1,1 });
	drawLine(drawList, { 366,106 }, { 366,67 }, { 1,1,1,1 });
	drawLine(drawList, { 334,87 }, { 366,87 }, { 1,1,1,1 });
	drawLine(drawList, { 340,89 }, { 340,87 }, { 1,1,1,1 });
	drawLine(drawList, { 366,67 }, { 333,67 }, { 1,1,1,1 });
	drawLine(drawList, { 333,67 }, { 333,59 }, { 1,1,1,1 });
	drawLine(drawList, { 333,59 }, { 322,59 }, { 1,1,1,1 });
	drawLine(drawList, { 322,59 }, { 322,65 }, { 1,1,1,1 });
	drawLine(drawList, { 322,65 }, { 317,59 }, { 1,1,1,1 });
	drawLine(drawList, { 317,59 }, { 303,59 }, { 1,1,1,1 });
	drawLine(drawList, { 303,59 }, { 298,64 }, { 1,1,1,1 });
	drawLine(drawList, { 298,64 }, { 298,70 }, { 1,1,1,1 });
	drawLine(drawList, { 342,106 }, { 298,106 }, { 1,1,1,1 });
	drawLine(drawList, { 298,106 }, { 298,85 }, { 1,1,1,1 });
	drawLine(drawList, { 295,87 }, { 321,87 }, { 1,1,1,1 });
	drawLine(drawList, { 340,106 }, { 340,101 }, { 1,1,1,1 });
	drawLine(drawList, { 321,106 }, { 321,104 }, { 1,1,1,1 });
	drawLine(drawList, { 321,87 }, { 321,95 }, { 1,1,1,1 });
	drawLine(drawList, { 298,67 }, { 238,67 }, { 1,1,1,1 });
	drawLine(drawList, { 238,67 }, { 238,88 }, { 1,1,1,1 });
	drawLine(drawList, { 298,103 }, { 238,103 }, { 1,1,1,1 });
	drawLine(drawList, { 238,103 }, { 238,100 }, { 1,1,1,1 });
	drawLine(drawList, { 238,86 }, { 247,86 }, { 1,1,1,1 });
	drawLine(drawList, { 258,86 }, { 267,86 }, { 1,1,1,1 });
	drawLine(drawList, { 267,87 }, { 267,67 }, { 1,1,1,1 });
	drawLine(drawList, { 283,87 }, { 267,87 }, { 1,1,1,1 });
	if (showAreas) {
		drawText(drawList, { 160,25 }, { 1,1,1,1 }, "Drop\nShip");
		drawText(drawList, { 58,105 }, { 1,1,1,1 }, "Sec.");
		drawText(drawList, { 175,144 }, { 1,1,1,1 }, "Office");
		drawText(drawList, { 314,165 }, { 1,1,1,1 }, "Spec.");
		drawText(drawList, { 98,100 }, { 1,1,1,1 }, "Elec.");
		drawText(drawList, { 188,100 }, { 1,1,1,1 }, "Stor.");
		drawText(drawList, { 202,181 }, { 1,1,1,1 }, "Admin");
		drawText(drawList, { 51,137 }, { 1,1,1,1 }, "O2");
		drawText(drawList, { 123,192 }, { 1,1,1,1 }, "Weps.");
		drawText(drawList, { 272,70 }, { 1,1,1,1 }, "Lab");
		drawText(drawList, { 126,142 }, { 1,1,1,1 }, "Com");
	}
	if (showVents) {
		drawRect(drawList, { 301,89 }, { 304,91 }, { 1,0,0,1 });
		drawRect(drawList, { 287,106 }, { 290,108 }, { 1,0,0,1 });
		drawRect(drawList, { 200,215 }, { 203,217 }, { 1,0,0,1 });
		drawRect(drawList, { 190,204 }, { 193,206 }, { 1,0,0,1 });

		drawRect(drawList, { 71,143 }, { 74,145 }, { 0,1,0,1 });
		drawRect(drawList, { 59,87 }, { 62,89 }, { 0,1,0,1 });
		drawRect(drawList, { 97,129 }, { 100,131 }, { 0,1,0,1 });

		drawRect(drawList, { 216,113 }, { 219,111 }, { 1,1,0,1 });
		drawRect(drawList, { 170,169 }, { 173,171 }, { 1,1,0,1 });
		drawRect(drawList, { 138,161 }, { 141,163 }, { 1,1,0,1 });

		drawRect(drawList, { 231,83 }, { 234,85 }, { 0,0,1,1 });
		drawRect(drawList, { 121,78 }, { 124,80 }, { 0,0,1,1 });
	}

	drawPlayers(drawList, playerSize);
}

void skeld() {
	if (!isDebug)
		setMapSettings(9.157,457.831,0.482f,-8.434,144.578,0.482f);
	ImDrawList* drawList = ImGui::GetBackgroundDrawList();
	drawRect(drawList, { 0,0 }, { 400,230 }, { 0,0,0,BACKGROUNDALPHA});
	drawLine(drawList,{ 44,52 }, { 54,42 }, { 1,1,1,1 });
	drawLine(drawList,{ 54,42 }, { 87,42 }, { 1,1,1,1 });
	drawLine(drawList,{ 87,42 }, { 87,53 }, { 1,1,1,1 });
	drawLine(drawList,{ 87,53 }, { 162,53 }, { 1,1,1,1 });
	drawLine(drawList,{ 162,53 }, { 162,33 }, { 1,1,1,1 });
	drawLine(drawList,{ 162,33 }, { 180,15 }, { 1,1,1,1 });
	drawLine(drawList,{ 180,15 }, { 236,15 }, { 1,1,1,1 });
	drawLine(drawList,{ 236,15 }, { 263,41 }, { 1,1,1,1 });
	drawLine(drawList,{ 263,41 }, { 263,53 }, { 1,1,1,1 });
	drawLine(drawList,{ 263,53 }, { 280,53 }, { 1,1,1,1 });
	drawLine(drawList,{ 280,53 }, { 280,36 }, { 1,1,1,1 });
	drawLine(drawList,{ 280,36 }, { 303,36 }, { 1,1,1,1 });
	drawLine(drawList,{ 303,36 }, { 322,55 }, { 1,1,1,1 });
	drawLine(drawList,{ 322,55 }, { 322,82 }, { 1,1,1,1 });
	drawLine(drawList,{ 322,82 }, { 310,82 }, { 1,1,1,1 });
	drawLine(drawList,{ 310,82 }, { 310,91 }, { 1,1,1,1 });
	drawLine(drawList,{ 310,91 }, { 331,91 }, { 1,1,1,1 });
	drawLine(drawList,{ 331,91 }, { 331,103 }, { 1,1,1,1 });
	drawLine(drawList,{ 331,103 }, { 356,103 }, { 1,1,1,1 });
	drawLine(drawList,{ 356,103 }, { 356,91 }, { 1,1,1,1 });
	drawLine(drawList,{ 356,91 }, { 374,91 }, { 1,1,1,1 });
	drawLine(drawList,{ 374,91 }, { 388,103 }, { 1,1,1,1 });
	drawLine(drawList,{ 388,103 }, { 388,120 }, { 1,1,1,1 });
	drawLine(drawList,{ 388,120 }, { 374,132 }, { 1,1,1,1 });
	drawLine(drawList,{ 374,132 }, { 356,132 }, { 1,1,1,1 });
	drawLine(drawList,{ 356,132 }, { 356,120 }, { 1,1,1,1 });
	drawLine(drawList,{ 356,120 }, { 331,120 }, { 1,1,1,1 });
	drawLine(drawList,{ 331,120 }, { 331,135 }, { 1,1,1,1 });
	drawLine(drawList,{ 331,135 }, { 310,135 }, { 1,1,1,1 });
	drawLine(drawList,{ 310,135 }, { 310,157 }, { 1,1,1,1 });
	drawLine(drawList,{ 310,157 }, { 322,157 }, { 1,1,1,1 });
	drawLine(drawList,{ 322,157 }, { 322,185 }, { 1,1,1,1 });
	drawLine(drawList,{ 322,185 }, { 303,203 }, { 1,1,1,1 });
	drawLine(drawList,{ 303,203 }, { 280,203 }, { 1,1,1,1 });
	drawLine(drawList,{ 280,203 }, { 280,185 }, { 1,1,1,1 });
	drawLine(drawList,{ 280,185 }, { 271,185 }, { 1,1,1,1 });
	drawLine(drawList,{ 271,185 }, { 271,191 }, { 1,1,1,1 });
	drawLine(drawList,{ 271,191 }, { 277,191 }, { 1,1,1,1 });
	drawLine(drawList,{ 277,191 }, { 277,216 }, { 1,1,1,1 });
	drawLine(drawList,{ 277,216 }, { 267,225 }, { 1,1,1,1 });
	drawLine(drawList,{ 267,225 }, { 240,225 }, { 1,1,1,1 });
	drawLine(drawList,{ 240,225 }, { 231,216 }, { 1,1,1,1 });
	drawLine(drawList,{ 231,216 }, { 231,191 }, { 1,1,1,1 });
	drawLine(drawList,{ 231,191 }, { 256,191 }, { 1,1,1,1 });
	drawLine(drawList,{ 256,191 }, { 256,185 }, { 1,1,1,1 });
	drawLine(drawList,{ 256,185 }, { 227,185 }, { 1,1,1,1 });
	drawLine(drawList,{ 227,185 }, { 227,225 }, { 1,1,1,1 });
	drawLine(drawList,{ 227,225 }, { 191,225 }, { 1,1,1,1 });
	drawLine(drawList,{ 191,225 }, { 172,207 }, { 1,1,1,1 });
	drawLine(drawList,{ 172,207 }, { 172,205 }, { 1,1,1,1 });
	drawLine(drawList,{ 172,205 }, { 103,205 }, { 1,1,1,1 });
	drawLine(drawList,{ 103,205 }, { 103,180 }, { 1,1,1,1 });
	drawLine(drawList,{ 103,180 }, { 87,180 }, { 1,1,1,1 });
	drawLine(drawList,{ 87,180 }, { 87,195 }, { 1,1,1,1 });
	drawLine(drawList,{ 87,195 }, { 55,195 }, { 1,1,1,1 });
	drawLine(drawList,{ 55,195 }, { 44,186 }, { 1,1,1,1 });
	drawLine(drawList,{ 44,186 }, { 44,149 }, { 1,1,1,1 });
	drawLine(drawList,{ 44,149 }, { 60,149 }, { 1,1,1,1 });
	drawLine(drawList,{ 60,149 }, { 60,126 }, { 1,1,1,1 });
	drawLine(drawList,{ 60,126 }, { 48,126 }, { 1,1,1,1 });
	drawLine(drawList,{ 48,126 }, { 48,138 }, { 1,1,1,1 });
	drawLine(drawList,{ 48,138 }, { 34,138 }, { 1,1,1,1 });
	drawLine(drawList,{ 34,138 }, { 34,152 }, { 1,1,1,1 });
	drawLine(drawList,{ 34,152 }, { 24,152 }, { 1,1,1,1 });
	drawLine(drawList,{ 24,152 }, { 9,143 }, { 1,1,1,1 });
	drawLine(drawList,{ 9,143 }, { 9,92 }, { 1,1,1,1 });
	drawLine(drawList,{ 9,92 }, { 25,82 }, { 1,1,1,1 });
	drawLine(drawList,{ 25,82 }, { 34,82 }, { 1,1,1,1 });
	drawLine(drawList,{ 34,82 }, { 34,97 }, { 1,1,1,1 });
	drawLine(drawList,{ 34,97 }, { 48,97 }, { 1,1,1,1 });
	drawLine(drawList,{ 48,97 }, { 48,109 }, { 1,1,1,1 });
	drawLine(drawList,{ 48,109 }, { 60,109 }, { 1,1,1,1 });
	drawLine(drawList,{ 60,109 }, { 60,88 }, { 1,1,1,1 });
	drawLine(drawList,{ 60,88 }, { 44,88 }, { 1,1,1,1 });
	drawLine(drawList,{ 44,88 }, { 44,52 }, { 1,1,1,1 });
	// east inside
	drawLine(drawList,{ 263,71 }, { 280,71 }, { 1,1,1,1 });
	drawLine(drawList,{ 280,71 }, { 280,73 }, { 1,1,1,1 });
	drawLine(drawList,{ 280,73 }, { 290,82 }, { 1,1,1,1 });
	drawLine(drawList,{ 290,82 }, { 295,82 }, { 1,1,1,1 });
	drawLine(drawList,{ 295,82 }, { 295,91 }, { 1,1,1,1 });
	drawLine(drawList,{ 295,91 }, { 288,91 }, { 1,1,1,1 });
	drawLine(drawList,{ 288,91 }, { 288,88 }, { 1,1,1,1 });
	drawLine(drawList,{ 288,88 }, { 268,88 }, { 1,1,1,1 });
	drawLine(drawList,{ 268,88 }, { 268,91 }, { 1,1,1,1 });
	drawLine(drawList,{ 268,91 }, { 254,105 }, { 1,1,1,1 });
	drawLine(drawList,{ 254,105 }, { 254,118 }, { 1,1,1,1 });
	drawLine(drawList,{ 254,118 }, { 288,118 }, { 1,1,1,1 });
	drawLine(drawList,{ 288,118 }, { 288,108 }, { 1,1,1,1 });
	drawLine(drawList,{ 288,108 }, { 316,108 }, { 1,1,1,1 });
	drawLine(drawList,{ 316,108 }, { 316,117 }, { 1,1,1,1 });
	drawLine(drawList,{ 316,117 }, { 295,117 }, { 1,1,1,1 });
	drawLine(drawList,{ 295,117 }, { 295,157 }, { 1,1,1,1 });
	drawLine(drawList,{ 295,157 }, { 290,157 }, { 1,1,1,1 });
	drawLine(drawList,{ 290,157 }, { 280,166 }, { 1,1,1,1 });
	drawLine(drawList,{ 280,166 }, { 280,168 }, { 1,1,1,1 });
	drawLine(drawList,{ 280,168 }, { 227,168 }, { 1,1,1,1 });
	drawLine(drawList,{ 227,168 }, { 227,145 }, { 1,1,1,1 });
	drawLine(drawList,{ 227,145 }, { 219,145 }, { 1,1,1,1 });
	drawLine(drawList,{ 219,145 }, { 219,141 }, { 1,1,1,1 });
	drawLine(drawList,{ 219,141 }, { 235,141 }, { 1,1,1,1 });
	drawLine(drawList,{ 235,141 }, { 235,163 }, { 1,1,1,1 });
	drawLine(drawList,{ 235,163 }, { 273,163 }, { 1,1,1,1 });
	drawLine(drawList,{ 273,163 }, { 281,155 }, { 1,1,1,1 });
	drawLine(drawList,{ 281,155 }, { 281,124 }, { 1,1,1,1 });
	drawLine(drawList,{ 281,124 }, { 219,124 }, { 1,1,1,1 });
	drawLine(drawList,{ 219,124 }, { 219,113 }, { 1,1,1,1 });
	drawLine(drawList,{ 219,113 }, { 240,113 }, { 1,1,1,1 });
	drawLine(drawList,{ 240,113 }, { 263,91 }, { 1,1,1,1 });
	drawLine(drawList,{ 263,91 }, { 263,71 }, { 1,1,1,1 });
	// west inside
	drawLine(drawList,{ 87,71 }, { 129,71 }, { 1,1,1,1 });
	drawLine(drawList,{ 129,71 }, { 129,76 }, { 1,1,1,1 });
	drawLine(drawList,{ 129,76 }, { 118,76 }, { 1,1,1,1 });
	drawLine(drawList,{ 118,76 }, { 118,115 }, { 1,1,1,1 });
	drawLine(drawList,{ 118,115 }, { 126,125 }, { 1,1,1,1 });
	drawLine(drawList,{ 126,125 }, { 173,125 }, { 1,1,1,1 });
	drawLine(drawList,{ 173,125 }, { 173,113 }, { 1,1,1,1 });
	drawLine(drawList,{ 173,113 }, { 157,98 }, { 1,1,1,1 });
	drawLine(drawList,{ 157,98 }, { 157,76 }, { 1,1,1,1 });
	drawLine(drawList,{ 157,76 }, { 144,76 }, { 1,1,1,1 });
	drawLine(drawList,{ 144,76 }, { 144,71 }, { 1,1,1,1 });
	drawLine(drawList,{ 144,71 }, { 162,71 }, { 1,1,1,1 });
	drawLine(drawList,{ 162,71 }, { 162,91 }, { 1,1,1,1 });
	drawLine(drawList,{ 162,91 }, { 184,113 }, { 1,1,1,1 });
	drawLine(drawList,{ 184,113 }, { 204,113 }, { 1,1,1,1 });
	drawLine(drawList,{ 204,113 }, { 204,145 }, { 1,1,1,1 });
	drawLine(drawList,{ 204,145 }, { 186,145 }, { 1,1,1,1 });
	drawLine(drawList,{ 186,145 }, { 172,159 }, { 1,1,1,1 });
	drawLine(drawList,{ 172,159 }, { 172,187 }, { 1,1,1,1 });
	drawLine(drawList,{ 172,187 }, { 140,187 }, { 1,1,1,1 });
	drawLine(drawList,{ 140,187 }, { 140,182 }, { 1,1,1,1 });
	drawLine(drawList,{ 140,182 }, { 152,182 }, { 1,1,1,1 });
	drawLine(drawList,{ 152,182 }, { 161,174 }, { 1,1,1,1 });
	drawLine(drawList,{ 161,174 }, { 161,155 }, { 1,1,1,1 });
	drawLine(drawList,{ 161,155 }, { 173,144 }, { 1,1,1,1 });
	drawLine(drawList,{ 173,144 }, { 173,133 }, { 1,1,1,1 });
	drawLine(drawList,{ 173,133 }, { 126,133 }, { 1,1,1,1 });
	drawLine(drawList,{ 126,133 }, { 126,188 }, { 1,1,1,1 });
	drawLine(drawList,{ 126,188 }, { 118,188 }, { 1,1,1,1 });
	drawLine(drawList,{ 118,188 }, { 118,163 }, { 1,1,1,1 });
	drawLine(drawList,{ 118,163 }, { 87,163 }, { 1,1,1,1 });
	drawLine(drawList,{ 87,163 }, { 87,149 }, { 1,1,1,1 });
	drawLine(drawList,{ 87,149 }, { 75,149 }, { 1,1,1,1 });
	drawLine(drawList,{ 75,149 }, { 75,127 }, { 1,1,1,1 });
	drawLine(drawList,{ 75,127 }, { 88,127 }, { 1,1,1,1 });
	drawLine(drawList,{ 88,127 }, { 88,137 }, { 1,1,1,1 });
	drawLine(drawList,{ 88,137 }, { 113,137 }, { 1,1,1,1 });
	drawLine(drawList,{ 113,137 }, { 113,97 }, { 1,1,1,1 });
	drawLine(drawList,{ 113,97 }, { 107,91 }, { 1,1,1,1 });
	drawLine(drawList,{ 107,91 }, { 97,91 }, { 1,1,1,1 });
	drawLine(drawList,{ 97,91 }, { 88,99 }, { 1,1,1,1 });
	drawLine(drawList,{ 88,99 }, { 88,109 }, { 1,1,1,1 });
	drawLine(drawList,{ 88,109 }, { 75,109 }, { 1,1,1,1 });
	drawLine(drawList,{ 75,109 }, { 75,88 }, { 1,1,1,1 });
	drawLine(drawList,{ 75,88 }, { 87,88 }, { 1,1,1,1 });
	drawLine(drawList,{ 87,88 }, { 87,71 }, { 1,1,1,1 });
	//info
	if (showAreas) {
		drawText(drawList, { 180,47 }, { 1,1,1,1 }, "Cafeteria");
		drawText(drawList, { 125,82 }, { 1,1,1,1 }, "Med");
		drawText(drawList, { 85,110 }, { 1,1,1,1 }, "Sec.");
		drawText(drawList, { 45,48 }, { 1,1,1,1 }, "Upper\nEngine");
		drawText(drawList, { 10,110 }, { 1,1,1,1 }, "Reactor");
		drawText(drawList, { 45,153 }, { 1,1,1,1 }, "Lower\nEngine");
		drawText(drawList, { 130,137 }, { 1,1,1,1 }, "Elec.");
		drawText(drawList, { 175,162 }, { 1,1,1,1 }, "Storage");
		drawText(drawList, { 240,128 }, { 1,1,1,1 }, "Admin");
		drawText(drawList, { 272,92 }, { 1,1,1,1 }, "O2");
		drawText(drawList, { 285,55 }, { 1,1,1,1 }, "Weps.");
		drawText(drawList, { 360,105 }, { 1,1,1,1 }, "Nav");
		drawText(drawList, { 280,170 }, { 1,1,1,1 }, "Shields");
		drawText(drawList, { 235,195 }, { 1,1,1,1 }, "Comms");
	}
	// vents
	if (showVents) {
		drawRect(drawList, { 256,76 }, { 259,78 }, { 1,0,0,1 });
		drawRect(drawList, { 298,121 }, { 301,123 }, { 1,0,0,1 });
		drawRect(drawList, { 239,157 }, { 242,159 }, { 1,0,0,1 });

		drawRect(drawList, { 122,111 }, { 125,113 }, { 0,1,0,1 });
		drawRect(drawList, { 130,137 }, { 133,139 }, { 0,1,0,1 });
		drawRect(drawList, { 106,131 }, { 109,129 }, { 0,1,0,1 });

		drawRect(drawList, { 80,189 }, { 83,191 }, { 0,0,1,1 });
		drawRect(drawList, { 34,132 }, { 37,134 }, { 0,0,1,1 });

		drawRect(drawList, { 80,50 }, { 83,52 }, { 0,1,1,1 });
		drawRect(drawList, { 25,96 }, { 28,98 }, { 0,1,1,1 });

		drawRect(drawList, { 298,195 }, { 301,197 }, { 1,0,1,1 });
		drawRect(drawList, { 360,128 }, { 363,126 }, { 1,0,1,1 });

		drawRect(drawList, { 363,97 }, { 360,95 }, { 1,1,1,1 });
		drawRect(drawList, { 296,41 }, { 299,43 }, { 1,1,1,1 });
	}

	drawPlayers(drawList, playerSize);
}

std::string Hats[94]{
	"Empty",
	"Astronaut",
	"Backwards Cap",
	"Blob Alien",
	"Coyote Petersons Hat",
	"Captains Hat",
	"Triple Tophat",
	"Flower Pot",
	"Flight Goggles",
	"Hardhat",
	"Generals Cap",
	"Paper Boat",
	"Party Hat",
	"Police Hat",
	"Head Mirror",
	"Tophat",
	"Turban",
	"Ushanka",
	"Viking",
	"Security Cap",
	"Snowman",
	"Antlers",
	"Christmas Lights",
	"Santa's Hat",
	"Christmas Tree",
	"Christmas Gift",
	"Candycane Antlers",
	"Elf's Hat",
	"New Years Hat",
	"White Tophat",
	"Crown",
	"Eyebrows",
	"Halo",
	"Elf Hat #2",
	"Oldman Hat",
	"Plunger",
	"Snorkle",
	"Stickman",
	"Safari Man",
	"Sheriffs Hat",
	"Alien Eye",
	"Toilet Paper",
	"Thanksgiving Tophat",
	"Fedora",
	"Goggles",
	"Headphones",
	"Hazmat",
	"Mask",
	"TotallyNotSus",
	"Straw Hat",
	"Bananna Peel",
	"H3H3 Beanie",
	"Bear Ears",
	"Cheese Wedge",
	"Apple",
	"Sunnyside Up Egg",
	"Green Fedora",
	"Flamingo",
	"Flower",
	"Knight",
	"Leaf",
	"Kitten Hat",
	"Bat Wings",
	"Devil Horns",
	"Seamonster",
	"Pumpkin",
	"Scary Bag",
	"Witch Hat",
	"Werewolf",
	"Pirates Hat",
	"Doctor of Death",
	"Knife in Head",
	"Jason Mask",
	"Miner Helmet",
	"Ugly Beanie",
	"Frozen Hat",
	"Antenna",
	"Black Balloon",
	"Birds Nest",
	"Ninja",
	"Pissy Floor Sign",
	"Chef",
	"Conductors Cap",
	"Bandana",
	"Dum",
	"Fez",
	"General Cap",
	"Elvis",
	"Squid Billies",
	"Army Helmet",
	"Miniyou",
	"Thief",
	"Horns",
	"Snowy You"
};

std::string Pets[11] {
	"Broke Boy",
	"Blob Alien",
	"Miniyou",
	"Doggy",
	"Stickman",
	"Hamster",
	"Robot",
	"UFO",
	"Stickman with Helmet",
	"Tentacle Alien",
	"Headcrab"
};

std::string Skins[16]{
	"Naked",
	"Astronaut",
	"Aircraft Pilot",
	"Mechanic",
	"Army",
	"Police Uniform",
	"Doctor",
	"Business Suit",
	"White Business Suit",
	"Security",
	"Hazmat",
	"Scientist",
	"Construction Worker",
	"Overralls",
	"Winter Jacket",
	"Indiana Jones",
};

std::string Colors[12]{
	"Red",
	"Blue",
	"Dark Green",
	"Pink",
	"Orange",
	"Yellow",
	"Black",
	"White",
	"Purple",
	"Brown",
	"Cyan",
	"Lime"
};
#endif