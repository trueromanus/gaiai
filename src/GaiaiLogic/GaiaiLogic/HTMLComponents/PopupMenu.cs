using EmptyFlow.SciterAPI;
using System;
using System.Collections.Generic;
using System.Text;

namespace GaiaiLogic.HTMLComponents
{

    internal record PopupMenuItem(string Title, string Action, bool Enabled, bool Terminator);

    internal class PopupMenu : SciterEventHandler
    {

        private readonly List<PopupMenuItem> m_items;

        public PopupMenu(nint relatedThing, SciterAPIHost host) : base(relatedThing, host)
        {
            m_items = new List<PopupMenuItem>();

            var childrens = Host.GetElementChildrens(relatedThing);
            foreach (var child in childrens)
            {
                var action = Host.GetElementAttribute(child, "action");
                var content = Host.GetElementHtml(child, false);
                var terminator = Host.GetElementHasAttribute(child, "terminator");
                var enabled = Host.GetElementHasAttribute(child, "enabled");
                m_items.Add(new PopupMenuItem(content, action, enabled, terminator));
            }

        }

        public void ClickOnMenu(ItemPopupMenu menu)
        {

        }

        public void HoverOnMenu(ItemPopupMenu menu)
        {

        }

        public override EventBehaviourGroups BeforeRegisterEvent() => EventBehaviourGroups.HANDLE_BEHAVIOR_EVENT;

    }
}
