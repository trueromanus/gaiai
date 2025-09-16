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

    }

}
