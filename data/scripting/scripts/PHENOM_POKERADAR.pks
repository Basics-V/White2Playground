import system.Runtime;
import system.text.WordSet;
import event.dialogs.Message;
import system.Sound;
import system.EventWorks;
import event.Effects;
import event.actors.Player;
import system.Input;
import system.Runtime;

// Global script IDs at 20800
// Size of file must match GlobalScript.h
public class PHENOM_POKERADAR {
    // 20800
	public static void useFailed() {
        WordSet.LoadPlayerName(0);
        systemMessage(0);
		Runtime.FinishSubEvents();
	}

	// 20801
	public static void useSuccess() {
        int radarWk = EventWorks.Get(16404);
        if (radarWk == 2) {
            return useFailed();
        } else if (radarWk == 0) {
            Sound.BGMFadeOut(60);

            Player.SetSpecialSequence(16);
            UseItemAction(255);

            WordSet.LoadPlayerName(0);
            systemMessage(1);

            //Effects.Play(76);

            Player.SetSpecialSequence(8);

            EventWorks.Set(16404, 1);
        } else if (radarWk == 4) {
            Sound.BGMFadeOut(60);
            EventWorks.Set(16404, 1);
            radarWk = 0;
        }

        Sound.SEPlay(1599);
        Message.System(2, 0);
        Runtime.Sleep(30);
		Message.CloseAll();
        Sound.SEStop();

        Sound.SEPlay(2060);
        Runtime.Sleep(60);
        Sound.SEStop();

        systemMessage(3);
        if (radarWk == 0) {
            Sound.BGMPlay(1068);
        }

		Runtime.FinishSubEvents();
	}

    static void systemMessage(int msgID) {
        Message.System(msgID, 0);
		Input.LastKeyWait();
		Message.CloseAll();
    }

	static meta void UseItemAction(int actorID): VActionSequence {
		DoItemGetHop(1);
	}

	static native void DoItemGetHop(int amount): 0x9a;
}
