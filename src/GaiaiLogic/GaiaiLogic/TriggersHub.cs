namespace GaiaiLogic {

    /// <summary>
    /// Class which is store happened triggers.
    /// </summary>
    internal class TriggersHub {

        public readonly HashSet<string> m_triggeredThings = [];

        public bool TriggerIsEnabled ( string trigger ) => m_triggeredThings.Contains ( trigger );

        public void EnableTrigger ( string trigger ) {
            if ( m_triggeredThings.Contains ( trigger ) ) return;

            m_triggeredThings.Add ( trigger );
        }

        public void DisableTrigger ( string trigger ) {
            if ( !m_triggeredThings.Contains ( trigger ) ) return;

            m_triggeredThings.Remove ( trigger );
        }

    }

}
