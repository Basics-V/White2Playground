import system.Runtime;
import system.text.WordSet;
import event.dialogs.Message;
import system.Sound;
import system.EventWorks;
import event.Effects;
import event.actors.Player;
import system.Field;
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
	public static void spawnFail() {
        if (EventWorks.Get(16404) == 0) {
            useCutscene();
        } else {
            Sound.BGMFadeOut(60);
            Sound.SEPlay(1599);
        }
        EventWorks.Set(16404, 4);

        Message.System(2, 0);
        Runtime.Sleep(30);
		Message.CloseAll();
        Sound.SEStop();

        Field.PlayMapBGM();
        systemMessage(4);

		Runtime.FinishSubEvents();
	}

	// 20802
	public static void useSuccess() {
        int radarWk = EventWorks.Get(16404);
        if (radarWk == 2) {
            return useFailed();
        } else if (radarWk == 0) {
            useCutscene();
            EventWorks.Set(16404, 1);
        } else if (radarWk == 4) {
            Sound.BGMFadeOut(60);
            EventWorks.Set(16404, 1);
            radarWk = 0;
            Sound.SEPlay(1599);
        }

        if (radarWk != 0) {
            Sound.SEPlay(1599);
        }
        Message.System(2, 0);
        Runtime.Sleep(30);
		Message.CloseAll();
        Sound.SEStop();

        Sound.SEPlay(2060);
        Runtime.Sleep(20);
        Sound.SEStop();

        if (radarWk == 0) {
            Sound.BGMPlay(1068);
        }
        systemMessage(3);

		Runtime.FinishSubEvents();
	}

    static void useCutscene() {
        Sound.BGMFadeOut(60);

        Player.SetSpecialSequence(16);
        UseItemAction(255);

        WordSet.LoadPlayerName(0);
        systemMessage(1);

        int radarWk = EventWorks.Get(16404);
        EventWorks.Set(16404, 5); // For special effect
        //Sound.SEPlay(1675);
        Sound.SEPlay(1599);
        Effects.Play(50);
        //Sound.SEStop();
        EventWorks.Set(16404, radarWk); // Reset special effect

        Player.SetSpecialSequence(8);
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
