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
            host.EnableFeatures();
#endif

            RegisterSciterBehaviours.Register(host);

            host.CreateWindow(asMain: true, debugOutput: true);

            var customPage = Environment.GetEnvironmentVariable("custompage");
            if (string.IsNullOrEmpty(customPage))
            {
                host.LoadFile(@"home://HTMLGameData/game.html");
            }
            else
            {
                host.LoadFile(@"home://" + customPage);
            }


            host.SetWindowCaption(host.MainWindow, "gaiai");
            host.ShowWindow(host.MainWindow);
#if DEBUG
            //var console = new DeveloperConsole(host, host.MainWindow);
#endif
            host.Process();
        }

    }

}
