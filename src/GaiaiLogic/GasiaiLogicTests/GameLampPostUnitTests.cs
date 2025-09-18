using GaiaiLogic.Interactive;

namespace GaiaiLogicTests {

    public class GameLampPostUnitTests {

        [Fact]
        public void Constructor_Completed_Case1 () {
            // arrange and act
            var lampPost = new GameLampPost ( "", Enumerable.Empty<string> (), TimeSpan.Zero, 0 );

            // assert
            Assert.True ( lampPost.Correct );
        }

        [Fact]
        public void Constructor_Completed_Case2 () {
            // arrange and act
            var lampPost = new GameLampPost ( "Title", Enumerable.Empty<string> (), TimeSpan.Zero, 0 );

            // assert
            Assert.Equal ( "Title", lampPost.Title );
        }

        [Fact]
        public void Constructor_Completed_Case3 () {
            // arrange and act
            var lampPost = new GameLampPost ( "Title", Enumerable.Empty<string> (), TimeSpan.Zero, 30 );

            // assert
            Assert.Equal ( 30, lampPost.MaximumState );
        }

        [Fact]
        public void IsTurnOn_Completed_Case1 () {
            // arrange
            var lampPost = new GameLampPost ( "", Enumerable.Empty<string> (), new TimeSpan ( 3, 0, 0 ), 30 );

            // assert and act
            Assert.True ( lampPost.IsTurnOn ( new TimeSpan ( 0, 10, 0 ) ) );
            Assert.True ( lampPost.IsTurnOn ( new TimeSpan ( 0, 15, 0 ) ) );
            Assert.True ( lampPost.IsTurnOn ( new TimeSpan ( 0, 20, 0 ) ) );
            Assert.True ( lampPost.IsTurnOn ( new TimeSpan ( 0, 25, 0 ) ) );
            Assert.True ( lampPost.IsTurnOn ( new TimeSpan ( 0, 30, 0 ) ) );
        }

        [Fact]
        public void IsTurnOff_Completed_Case1 () {
            // arrange
            var lampPost = new GameLampPost ( "", Enumerable.Empty<string> (), new TimeSpan ( 3, 0, 0 ), 30 );

            // assert and act
            Assert.False ( lampPost.IsTurnOn ( new TimeSpan ( 22, 59, 0 ) ) );
            Assert.False ( lampPost.IsTurnOn ( new TimeSpan ( 22, 50, 0 ) ) );
            Assert.False ( lampPost.IsTurnOn ( new TimeSpan ( 1, 0, 0 ) ) );
            Assert.False ( lampPost.IsTurnOn ( new TimeSpan ( 4, 20, 0 ) ) );
            Assert.False ( lampPost.IsTurnOn ( new TimeSpan ( 8, 25, 0 ) ) );
        }

        [Fact]
        public void ParseContent_Completed_24Hours_Case1 () {
            // arrange
            var lampPost = new GameLampPost ( "", [], new TimeSpan ( 0, 0, 0 ), 30 );

            // act
            lampPost.ParseContent (
"""
turnon 12:00
turnoff 15:00
""",
    false
            );

            // assert
            Assert.Single ( lampPost.CurrentSchedulePairs );
            Assert.Equal ( new TimeSpan ( 12, 0, 0 ), lampPost.CurrentSchedulePairs.First ().start );
            Assert.Equal ( new TimeSpan ( 15, 0, 0 ), lampPost.CurrentSchedulePairs.First ().end );
        }

        [Fact]
        public void ParseContent_Completed_12Hours_Case1 () {
            // arrange
            var lampPost = new GameLampPost ( "", [], new TimeSpan ( 0, 0, 0 ), 30 );

            // act
            lampPost.ParseContent (
"""
turnon 12:00 pM
turnoff 03:00 Pm
""",
    true
            );

            // assert
            Assert.Single ( lampPost.CurrentSchedulePairs );
            Assert.Equal ( new TimeSpan ( 12, 0, 0 ), lampPost.CurrentSchedulePairs.First ().start );
            Assert.Equal ( new TimeSpan ( 15, 0, 0 ), lampPost.CurrentSchedulePairs.First ().end );
        }

        [Fact]
        public void ParseContent_Completed_Pairs_CorrectFewPairs () {
            // arrange
            var lampPost = new GameLampPost ( "", [], new TimeSpan ( 0, 0, 0 ), 30 );

            // act
            lampPost.ParseContent (
"""
turnon 12:00
turnoff 15:00
turnon 15:30
turnoff 16:40
turnon 17:30
turnoff 20:34
""",
    false
            );

            // assert
            Assert.Equal ( 3, lampPost.CurrentSchedulePairs.Count () );
            var first = lampPost.CurrentSchedulePairs.First ();
            var second = lampPost.CurrentSchedulePairs.ElementAt ( 1 );
            var third = lampPost.CurrentSchedulePairs.Last ();

            Assert.Equal ( new TimeSpan ( 12, 0, 0 ), first.start );
            Assert.Equal ( new TimeSpan ( 15, 0, 0 ), first.end );
            Assert.Equal ( new TimeSpan ( 15, 30, 0 ), second.start );
            Assert.Equal ( new TimeSpan ( 16, 40, 0 ), second.end );
            Assert.Equal ( new TimeSpan ( 17, 30, 0 ), third.start );
            Assert.Equal ( new TimeSpan ( 20, 34, 0 ), third.end );
        }

        [Fact]
        public void ParseContent_Completed_Pairs_NotCorrectOmitOn () {
            // arrange
            var lampPost = new GameLampPost ( "", [], new TimeSpan ( 0, 0, 0 ), 30 );

            // act
            lampPost.ParseContent (
"""
turnon 12:00
turnoff 15:00
turnoff 16:40
turnon 17:30
turnoff 20:34
""",
    false
            );

            // assert
            Assert.Equal ( 2, lampPost.CurrentSchedulePairs.Count () );
            var first = lampPost.CurrentSchedulePairs.First ();
            var second = lampPost.CurrentSchedulePairs.Last ();

            Assert.Equal ( new TimeSpan ( 12, 0, 0 ), first.start );
            Assert.Equal ( new TimeSpan ( 15, 0, 0 ), first.end );
            Assert.Equal ( new TimeSpan ( 17, 30, 0 ), second.start );
            Assert.Equal ( new TimeSpan ( 20, 34, 0 ), second.end );
        }

        [Fact]
        public void ParseContent_Completed_Pairs_NotCorrectOmitOff () {
            // arrange
            var lampPost = new GameLampPost ( "", [], new TimeSpan ( 0, 0, 0 ), 30 );

            // act
            lampPost.ParseContent (
"""
turnon 12:00
turnoff 15:00
turnon 16:00
turnon 17:30
turnoff 20:34
""",
    false
            );

            // assert
            Assert.Equal ( 2, lampPost.CurrentSchedulePairs.Count () );
            var first = lampPost.CurrentSchedulePairs.First ();
            var second = lampPost.CurrentSchedulePairs.Last ();

            Assert.Equal ( new TimeSpan ( 12, 0, 0 ), first.start );
            Assert.Equal ( new TimeSpan ( 15, 0, 0 ), first.end );
            Assert.Equal ( new TimeSpan ( 16, 0, 0 ), second.start );
            Assert.Equal ( new TimeSpan ( 20, 34, 0 ), second.end );
        }

        [Fact]
        public void ParseContent_Completed_Pairs_NotCorrectTime () {
            // arrange
            var lampPost = new GameLampPost ( "", [], new TimeSpan ( 0, 0, 0 ), 30 );

            // act
            lampPost.ParseContent (
"""
turnon 1:00
turnoff 15:00
turnon 16:00
turnoff 20:34
""",
    false
            );

            // assert
            Assert.Single ( lampPost.CurrentSchedulePairs );
            var first = lampPost.CurrentSchedulePairs.First ();

            Assert.Equal ( new TimeSpan ( 16, 0, 0 ), first.start );
            Assert.Equal ( new TimeSpan ( 20, 34, 0 ), first.end );
        }

        [Fact]
        public void ParseContent_Completed_Pairs_NotCorrectTime_Case2 () {
            // arrange
            var lampPost = new GameLampPost ( "", [], new TimeSpan ( 0, 0, 0 ), 30 );

            // act
            lampPost.ParseContent (
"""
turnon akjsfkjaskf daskj flasdj a
turnoff 15:00
turnon 16:00
turnoff 20:34
""",
    false
            );

            // assert
            Assert.Single ( lampPost.CurrentSchedulePairs );
            var first = lampPost.CurrentSchedulePairs.First ();

            Assert.Equal ( new TimeSpan ( 16, 0, 0 ), first.start );
            Assert.Equal ( new TimeSpan ( 20, 34, 0 ), first.end );
        }

    }

}
