import event.actors.Actor;
import event.dialogs.Message;
import system.Input;
import system.Runtime;
import system.text.WordSet;

// Global script IDs at 20850
// Size of file must match GlobalScript.h
public class BLOCK_HM {
    // 20850
	public static void fail() {
        WordSet.LoadPlayerName(0);
        Message.System(0, 2);
		Input.LastKeyWait();
		Message.CloseAll();
		Runtime.FinishSubEvents();
		Actor.UnpauseAll();
	}
}
