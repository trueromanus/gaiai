namespace GaiaiLogic {

    internal class Shift {

        private ShiftTimer m_shiftTimer = new ShiftTimer ();

        private City m_city = new City ();

        private CancellationTokenSource? m_cancellationTokenSource;

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

        public void Stop () {
            m_cancellationTokenSource?.Cancel ();
        }

    }

}
