using System.Globalization;

namespace GaiaiLogic.Interactive {

    internal record LampPostItem ( bool Mode, TimeSpan Minutes );

    internal class GameLampPost {

        private const string TurnOn = "turnon";

        private const string TurnOff = "turnoff";

        private readonly int m_maximumState;

        private readonly int m_currentState;

        public string Title { get; internal set; } = "";

        public List<LampPostItem> CurrentSchedule { get; internal set; }

        public List<(TimeSpan start, TimeSpan end)> CurrentSchedulePairs { get; internal set; } = new List<(TimeSpan start, TimeSpan end)> ();

        public IEnumerable<string> AffectedHouses { get; internal set; } = Enumerable.Empty<string> ();

        public GameLampPost ( string title, IEnumerable<string> affectedHouses, TimeSpan startTime, int maximumState ) {
            Title = title ?? throw new ArgumentNullException ( nameof ( title ) ); ;
            AffectedHouses = affectedHouses ?? throw new ArgumentNullException ( nameof ( affectedHouses ) );
            var random = new Random ( (int) ( DateTime.UtcNow - new DateTime ( 1970, 1, 1 ) ).TotalSeconds );

            m_maximumState = maximumState;
            m_currentState = m_maximumState;

            var time = new TimeSpan ( 21, 0, 0 ) + startTime;
            if ( time > new TimeSpan ( 23, 59, 59 ) ) time = time - new TimeSpan ( 23, 59, 59 );

            CurrentSchedule = new List<LampPostItem> {
                new LampPostItem (true, time),
                new LampPostItem (false, time + TimeSpan.FromMinutes(m_maximumState))
            };
            FillCurrentSchedulePairs ();
        }

        public int MaximumState => m_maximumState;

        public bool Correct => m_currentState <= m_maximumState;

        public bool IsTurnOn ( TimeSpan time ) {
            return CurrentSchedulePairs
                .Where ( a => a.start < a.end ? time >= a.start && time <= a.end : time >= a.start && time <= a.end )
                .Any ();
        }

        public void ParseContent ( string content, bool isAmPm ) {
            CurrentSchedule.Clear ();

            var lines = content.Split ( "\n" )
                .Select ( line => line.Trim ().ToLowerInvariant () )
                .Where ( a => !string.IsNullOrEmpty ( a ) )
                .ToList ();
            foreach ( var line in lines ) {
                if ( !( line.StartsWith ( TurnOff ) || line.StartsWith ( TurnOn ) ) ) continue;

                var turnOn = line.StartsWith ( TurnOn );
                TimeSpan timeValue = TimeSpan.Zero;

                var span = line.AsSpan ();
                var index = span.IndexOf ( ' ' );
                var slice = span.Slice ( index + 1 );
                try {
                    timeValue = ConvertTime ( slice.ToString (), isAmPm );

                    CurrentSchedule.Add ( new LampPostItem ( turnOn, timeValue ) );
                } catch {
                }
            }

            FillCurrentSchedulePairs ();
        }

        private static TimeSpan ConvertTime ( string time, bool isAmPm ) {
            if ( isAmPm ) {
                return DateTime.ParseExact ( time, "h:mm tt", CultureInfo.InvariantCulture ).TimeOfDay;
            } else {
                return DateTime.ParseExact ( time, "HH:mm", CultureInfo.InvariantCulture ).TimeOfDay;
            }
        }

        private void FillCurrentSchedulePairs () {
            TimeSpan? currentStartTime = null;
            CurrentSchedulePairs.Clear ();

            foreach ( var item in CurrentSchedule.OrderBy ( a => a.Minutes ) ) {
                if ( !currentStartTime.HasValue && item.Mode ) {
                    currentStartTime = item.Minutes;
                    continue;
                }
                if ( currentStartTime.HasValue && !item.Mode ) {
                    CurrentSchedulePairs.Add ( (currentStartTime.Value, item.Minutes) );
                    currentStartTime = null;
                }
            }
        }

    }

}
