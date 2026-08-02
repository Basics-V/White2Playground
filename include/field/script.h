// Riveting, I know...
struct ScriptVM;
struct FieldScriptEnv;

extern "C" {
    ScriptVM* EventScriptCall_Start(GameEvent*, u16, FieldActor*, void*, HeapID);
}
