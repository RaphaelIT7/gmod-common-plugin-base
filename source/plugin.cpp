#include "plugin.h"

// 
// The plugin is a static singleton that is exported as an interface
//
CServerPlugin g_EmtpyServerPlugin;
EXPOSE_SINGLE_INTERFACE_GLOBALVAR(CServerPlugin, IServerPluginCallbacks, INTERFACEVERSION_ISERVERPLUGINCALLBACKS, g_EmtpyServerPlugin );

//---------------------------------------------------------------------------------
// Purpose: constructor/destructor
//---------------------------------------------------------------------------------
CServerPlugin::CServerPlugin()
{
	m_iClientCommandIndex = 0;
}

CServerPlugin::~CServerPlugin()
{
}

//---------------------------------------------------------------------------------
// Purpose: called when the plugin is loaded, load the interface we need from the engine
//---------------------------------------------------------------------------------
bool CServerPlugin::Load(CreateInterfaceFn interfaceFactory, CreateInterfaceFn gameServerFactory)
{
	return true;
}

//---------------------------------------------------------------------------------
// Purpose: called when the plugin is unloaded (turned off)
//---------------------------------------------------------------------------------
void CServerPlugin::Unload(void)
{
}

//---------------------------------------------------------------------------------
// Purpose: called when the plugin is paused (i.e should stop running but isn't unloaded)
//---------------------------------------------------------------------------------
void CServerPlugin::Pause(void)
{
}

//---------------------------------------------------------------------------------
// Purpose: called when the plugin is unpaused (i.e should start executing again)
//---------------------------------------------------------------------------------
void CServerPlugin::UnPause(void)
{
}

//---------------------------------------------------------------------------------
// Purpose: the name of this plugin, returned in "plugin_print" command
//---------------------------------------------------------------------------------
const char * CServerPlugin::GetPluginDescription(void)
{
	return "Emtpy-Plugin V2, Valve";
}

//---------------------------------------------------------------------------------
// Purpose: called on level start
//---------------------------------------------------------------------------------
void CServerPlugin::LevelInit(char const *pMapName)
{
}

//---------------------------------------------------------------------------------
// Purpose: called after LUA Initialized.
//---------------------------------------------------------------------------------
bool CServerPlugin::LuaInit()
{
	LUA = GetRealm(GarrysMod::Lua::State::SERVER);
	if (LUA == nullptr) {
		Msg("Failed to initialize Server\n");
		return false;
	}

	// Add your code below.
	LUA->PushSpecial(GarrysMod::Lua::SPECIAL_GLOB);
		LUA->GetField(-1, "print");
			LUA->PushString("Hello World from a Plugin :D");
			LUA->Call(1, 0);
	LUA->Pop();

	return true;
}

//---------------------------------------------------------------------------------
// Purpose: called just before LUA is shutdown.
//---------------------------------------------------------------------------------
void CServerPlugin::LuaShutdown()
{
	LUA->PushSpecial(GarrysMod::Lua::SPECIAL_GLOB);
		LUA->GetField(-1, "print");
			LUA->PushString("Bye World from a Plugin :D");
			LUA->Call(1, 0);
	LUA->Pop();
}

//---------------------------------------------------------------------------------
// Purpose: called on level start, when the server is ready to accept client connections
//		edictCount is the number of entities in the level, clientMax is the max client count
//---------------------------------------------------------------------------------
void CServerPlugin::ServerActivate(edict_t *pEdictList, int edictCount, int clientMax)
{
	if (!lua_init) {
		lua_init = LuaInit();
	}
}

//---------------------------------------------------------------------------------
// Purpose: called once per server frame, do recurring work here (like checking for timeouts)
//---------------------------------------------------------------------------------
void CServerPlugin::GameFrame(bool simulating)
{
}

//---------------------------------------------------------------------------------
// Purpose: called on level end (as the server is shutting down or going to a new map)
//---------------------------------------------------------------------------------
void CServerPlugin::LevelShutdown(void) // !!!!this can get called multiple times per map change
{
	if (lua_init) {
		LuaShutdown();
		lua_init = false;
	}
}

//---------------------------------------------------------------------------------
// Purpose: called when a client spawns into a server (i.e as they begin to play)
//---------------------------------------------------------------------------------
void CServerPlugin::ClientActive(edict_t *pEntity)
{
}

//---------------------------------------------------------------------------------
// Purpose: called when a client leaves a server (or is timed out)
//---------------------------------------------------------------------------------
void CServerPlugin::ClientDisconnect(edict_t *pEntity)
{
}

//---------------------------------------------------------------------------------
// Purpose: called when a client spawns?
//---------------------------------------------------------------------------------
void CServerPlugin::ClientPutInServer(edict_t *pEntity, char const *playername)
{
}

//---------------------------------------------------------------------------------
// Purpose: called on level start
//---------------------------------------------------------------------------------
void CServerPlugin::SetCommandClient(int index)
{
	m_iClientCommandIndex = index;
}

void ClientPrint(edict_t *pEdict, char *format, ...)
{
	va_list		argptr;
	static char		string[1024];
	
	va_start (argptr, format);
	Q_vsnprintf(string, sizeof(string), format,argptr);
	va_end (argptr);
}
//---------------------------------------------------------------------------------
// Purpose: called on level start
//---------------------------------------------------------------------------------
void CServerPlugin::ClientSettingsChanged(edict_t *pEdict)
{
}

//---------------------------------------------------------------------------------
// Purpose: called when a client joins a server
//---------------------------------------------------------------------------------
PLUGIN_RESULT CServerPlugin::ClientConnect(bool *bAllowConnect, edict_t *pEntity, const char *pszName, const char *pszAddress, char *reject, int maxrejectlen)
{
	return PLUGIN_CONTINUE;
}

//---------------------------------------------------------------------------------
// Purpose: called when a client types in a command (only a subset of commands however, not CON_COMMAND's)
//---------------------------------------------------------------------------------
PLUGIN_RESULT CServerPlugin::ClientCommand(edict_t *pEntity, const CCommand &args)
{
	return PLUGIN_CONTINUE;
}

//---------------------------------------------------------------------------------
// Purpose: called when a client is authenticated
//---------------------------------------------------------------------------------
PLUGIN_RESULT CServerPlugin::NetworkIDValidated(const char *pszUserName, const char *pszNetworkID)
{
	return PLUGIN_CONTINUE;
}

//---------------------------------------------------------------------------------
// Purpose: called when a cvar value query is finished
//---------------------------------------------------------------------------------
void CServerPlugin::OnQueryCvarValueFinished(QueryCvarCookie_t iCookie, edict_t *pPlayerEntity, EQueryCvarValueStatus eStatus, const char *pCvarName, const char *pCvarValue)
{
}

void CServerPlugin::OnEdictAllocated(edict_t *edict)
{
}

void CServerPlugin::OnEdictFreed(const edict_t *edict)
{
}