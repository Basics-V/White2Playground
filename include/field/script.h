// Riveting, I know...
STRUCT_DECLARE(ScriptVM);
STRUCT_DECLARE(FieldScriptEnv);
struct ScriptVM;
struct FieldScriptEnv;

C_DECL_BEGIN
ScriptVM* EventScriptCall_Start(GameEvent*, u16, FieldActor*, void*, HeapID);
C_DECL_END
