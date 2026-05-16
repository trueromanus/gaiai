using EmptyFlow.SciterAPI;
using System;
using System.Collections.Generic;
using System.Text;

namespace GaiaiLogic.HTMLComponents
{

    internal record PopupMenuItem(string Title, string Action, bool Enabled, bool Terminator, int Id);

    internal class PopupMenu : SciterEventHandler
    {

        private readonly List<PopupMenuItem> m_items;

        private readonly Dictionary<int, PopupMenuItem> m_itemIds;

        public PopupMenu(nint relatedThing, SciterAPIHost host) : base(relatedThing, host)
        {
            m_items = new List<PopupMenuItem>();

            var childrens = Host.GetElementChildrens(relatedThing);
            var iterator = 0;
            foreach (var child in childrens)
            {
                var action = Host.GetElementAttribute(child, "action");
                var content = Host.GetElementHtml(child, false);
                var terminator = Host.GetElementHasAttribute(child, "terminator");
                var enabled = Host.GetElementHasAttribute(child, "enabled");
                m_items.Add(new PopupMenuItem(content, action, enabled, terminator, iterator));
                iterator++;
            }

            m_itemIds = m_items.ToDictionary(a => a.Id);

            RenderMenu();
        }

        private void RenderMenu()
        {
            var builder = new StringBuilder();
            foreach (var item in m_items)
            {
                if (item.Terminator)
                {
                    builder.AppendLine("""<div style="width:100%;height: 4px;" class="horizontal-dash-line"></div>""");
                    continue;
                }
                builder.AppendLine(
                    $$"""
                    <div style="width:100%; height: 24px; behavior: popupmenuitem;" class="flex-row text-middle-plus-size" menu-id="{{item.Id}}">
                        <div style="padding-left: 6px;" class="item-center">{{item.Title}}</div>
                    </div>
                    """
                );
            }

            Host.SetElementHtml(m_subscribedElement, builder.ToString(), SetElementHtml.ReplaceContent);
        }

        public void ClickOnMenu(ItemPopupMenu menu)
        {
            var item = m_itemIds[menu.MenuId];
            Host.ExecuteWindowEval(Host.MainWindow, item.Action, out _);
        }

        public void HoverOnMenu(ItemPopupMenu menu)
        {
            //TODO: implement showing sub menus
        }

        public override EventBehaviourGroups BeforeRegisterEvent() => EventBehaviourGroups.HANDLE_BEHAVIOR_EVENT;

    }
}
