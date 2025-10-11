using GaiaiLogic;

namespace FlowBridger.Export {

    public static partial class FlowBridgerExports {

        public static partial bool InitializeGameInternal ( string language ) => GameLibrary.InitializeGame ( language );

        public static partial bool RunTimerInternal () => GameLibrary.RunTimer();

        public static partial bool StopTimerInternal () => GameLibrary.StopTimer();

    }

}
