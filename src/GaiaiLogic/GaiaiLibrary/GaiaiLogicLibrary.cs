using System.Runtime.InteropServices;
using System.Text;

namespace FlowBridger.Export {
    public static partial class FlowBridgerExports {
        private static List<byte> m_zeroBytes = [0, 0, 0, 0];

        private static string GetUniStringFromPointer ( nint pointer ) {
            if ( RuntimeInformation.IsOSPlatform ( OSPlatform.Linux ) || RuntimeInformation.IsOSPlatform ( OSPlatform.OSX ) ) {
                if ( pointer == nint.Zero ) return "";

                var buffer = new List<byte> ();
                var offset = 0;
                while ( true ) {
                    var readedByte = Marshal.ReadByte ( pointer, offset );
                    offset++;

                    buffer.Add ( readedByte );

                    if ( buffer.Count () % 4 == 0 && buffer[^4..].SequenceEqual ( m_zeroBytes ) ) break;
                }

                if ( buffer.Count () == 4 && buffer.SequenceEqual ( m_zeroBytes ) ) return "";

                return Encoding.UTF8.GetString ( buffer.ToArray () ).Replace ( "\u0000", "" );
            }

            return Marshal.PtrToStringUni ( pointer ) ?? "";
        }

        [UnmanagedCallersOnly ( EntryPoint = "initialize_game" )]
        public static bool InitializeGame ( nint language ) {
            return InitializeGameInternal(Marshal.PtrToStringAnsi(language) ?? "");
        }

        public static partial bool InitializeGameInternal ( string language );

        [UnmanagedCallersOnly ( EntryPoint = "run_timer" )]
        public static bool RunTimer (  ) {
            return RunTimerInternal();
        }

        public static partial bool RunTimerInternal (  );

        [UnmanagedCallersOnly ( EntryPoint = "stop_timer" )]
        public static bool StopTimer (  ) {
            return StopTimerInternal();
        }

        public static partial bool StopTimerInternal (  );

    }
}