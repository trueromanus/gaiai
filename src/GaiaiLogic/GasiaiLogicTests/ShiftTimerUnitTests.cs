using GaiaiLogic;

namespace GaiaiLogicTests {

    public class ShiftTimerUnitTests {

        [Fact]
        public void Reset_Completed_WithoutChangedTime () {

            // arrange
            var shiftTimer = new ShiftTimer ();

            // act
            shiftTimer.Reset ();

            //assert
            Assert.Equal ( new TimeSpan ( 21, 0, 0 ), shiftTimer.CurrentTime );
        }

        [Fact]
        public void Reset_Completed_WithChangedTime () {

            // arrange
            var shiftTimer = new ShiftTimer ();
            shiftTimer.RunIteration ();
            shiftTimer.RunIteration ();
            shiftTimer.RunIteration ();

            // act
            shiftTimer.Reset ();

            //assert
            Assert.Equal ( new TimeSpan ( 21, 0, 0 ), shiftTimer.CurrentTime );
        }

        [Fact]
        public void RunIteration_Completed_TransitionOnNextDay () {

            // arrange
            var shiftTimer = new ShiftTimer ();
            for ( var i = 0; i < 35; i++ ) {
                shiftTimer.RunIteration ();
            }

            // act
            shiftTimer.RunIteration ();

            //assert
            Assert.Equal ( TimeSpan.Zero, shiftTimer.CurrentTime );
        }

    }

}
