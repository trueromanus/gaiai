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
                    await Task.Delay ( 5000, cancellationTokenSource.Token );

                    m_shiftTimer.RunIteration ();
                    m_city.ProcessEvents ( m_shiftTimer.CurrentTime );
                    //TODO: in random case add obstacles, count must be depending from shift count
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

    }

}
