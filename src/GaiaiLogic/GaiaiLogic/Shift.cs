using GaiaiLogic.Interactive;
using GaiaiLogic.Loaders;

namespace GaiaiLogic {

    internal class Shift {

        private ShiftTimer m_shiftTimer = new ShiftTimer ();

        private City m_city = new City ();

        private int m_day = 1;

        private CancellationTokenSource? m_mainProcessCancellationTokenSource;

        private readonly TriggersHub m_triggersHub;

        public Shift ( TriggersHub triggersHub ) {
            m_triggersHub = triggersHub ?? throw new ArgumentNullException ( nameof ( triggersHub ) );
        }

        public void Run () {
            CancellationTokenSource cancellationTokenSource = new ();

            Task.Run (
                async () => {
                    while ( true ) {
                        await Task.Delay ( 5000, cancellationTokenSource.Token );

                        m_shiftTimer.RunIteration ();
                        m_city.ProcessEvents ( m_shiftTimer.CurrentTime, m_triggersHub );
                    }
                },
                cancellationTokenSource.Token
            );
        }

        /// <summary>
        /// Close current opened shift.
        /// </summary>
        public void CloseShift () {
            if ( m_day == 8 ) {
                //TODO: need to close game
            }

            m_city.FinishAllProcesses ();
            m_shiftTimer.Reset ();
            m_day += 1;
        }

        public void Stop () {
            m_mainProcessCancellationTokenSource?.Cancel ();
        }

        /// <summary>
        /// Fill static items.
        /// </summary>
        /// <param name="items">Items.</param>
        public void FillStaticItems ( LoadedStaticItems items ) => m_city.FillData ( items );

        /// <summary>
        /// For test purposes!!!
        /// </summary>
        public IEnumerable<GameHouse> GetHouses() => m_city.GetHouses ();

        public IEnumerable<GameTrafficLight> GetTrafficLights () => m_city.GetTrafficLights ();

    }

}
