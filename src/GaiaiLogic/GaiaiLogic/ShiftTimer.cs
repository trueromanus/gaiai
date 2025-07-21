namespace GaiaiLogic {

    /// <summary>
    /// Shift timer.
    /// </summary>
    internal class ShiftTimer {

        private readonly TimeSpan m_startTime = new TimeSpan ( 21, 0, 0 );

        private TimeSpan m_currentTime;

        public ShiftTimer () {
            m_currentTime = m_startTime;
        }

        /// <summary>
        /// Current time.
        /// </summary>
        public TimeSpan CurrentTime => m_currentTime;

        /// <summary>
        /// Reset time to start of shift.
        /// </summary>
        public void Reset () {
            m_currentTime = m_startTime;
        }

        /// <summary>
        /// Run iteration and make step in time.
        /// </summary>
        public void RunIteration () {
            // if we have five minutes before midnight
            // we need to change time to make zero timespan because in other case it add to days TimeSpan which is not expected result
            if ( m_currentTime == new TimeSpan ( 23, 55, 0 ) ) {
                m_currentTime = TimeSpan.Zero;
                return;
            }
            m_currentTime += TimeSpan.FromMinutes ( 5 );
        }

    }

}
