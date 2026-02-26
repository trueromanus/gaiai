using EmptyFlow.SciterAPI;
using EmptyFlow.SciterAPI.Client.DeveloperConsole;

namespace GaiaiLogic {

    public static class Program {

        [STAThread]
        public static void Main() {
            var host = new SciterAPIHost(Environment.CurrentDirectory);
#if DEBUG
            host.EnableDebugMode();
#endif
            host.EnableFeatures(SciterRuntimeFeatures.ALLOW_SOCKET_IO);
            host.CreateWindow(asMain: true, debugOutput: true);
#if DEBUG
            host.LoadFile(@"C:\work\Repositories\HackingGame\game\gaiai\src\GaiaiLogic\GaiaiHTML\game.html");
            //host.LoadFile(@"C:\work\Repositories\HackingGame\game\gaiai\src\GaiaiLogic\GaiaiHTML\stylew95.html");
#endif
            host.SetWindowCaption(host.MainWindow, "gaiai");
            host.ShowWindow(host.MainWindow);
#if DEBUG
            var console = new DeveloperConsole(host, host.MainWindow);
#endif
            host.Process();
        }

    }

}
