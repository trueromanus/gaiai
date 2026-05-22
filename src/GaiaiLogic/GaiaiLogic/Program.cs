using EmptyFlow.SciterAPI;
using EmptyFlow.SciterAPI.Client.DeveloperConsole;
using GaiaiLogic.Translate;

namespace GaiaiLogic
{

    public static class Program
    {

        private static GameHost? m_gameHost = null;

        public static GameHost GameHost => m_gameHost ?? throw new ArgumentNullException(nameof(m_gameHost));

        [STAThread]
        public static void Main()
        {
            m_gameHost = new GameHost();
            m_gameHost.InitializeGame("en");

            var host = new SciterAPIHost(Environment.CurrentDirectory);
#if DEBUG
            host.EnableDebugMode();
#endif
            host.EnableFeatures();

            RegisterSciterBehaviours.Register(host);

            host.CreateWindow(asMain: true, debugOutput: true);
#if DEBUG
            //host.LoadFile(@"C:\work\Repositories\HackingGame\game\gaiai\src\GaiaiLogic\GaiaiHTML\stylew95.html");
            host.LoadFile(@"home://game.html");
#endif
            host.SetWindowCaption(host.MainWindow, "gaiai");
            host.ShowWindow(host.MainWindow);
#if DEBUG
            //var console = new DeveloperConsole(host, host.MainWindow);
#endif
            host.Process();
        }

    }

}
