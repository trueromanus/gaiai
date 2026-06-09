using EmptyFlow.SciterAPI;
using System;
using System.Collections.Generic;
using System.Text;

namespace GaiaiLogic.HTMLComponents
{

	internal class TreeItemModel
	{
		public int Index { get; set; }

		public string Name { get; set; } = "";

		public int Level { get; set; }

		public string? Icon { get; set; } = "";

		public string? OpenedIcon { get; set; } = "";

		public string? Command { get; set; } = "";

	}

	internal class TreeRoot : SciterEventHandler
	{

		private readonly List<int> SelectedItems = [];

		private readonly List<TreeItemModel> Tree = [];

		private readonly nint m_templateContainer;

		public TreeRoot(nint relatedThing, SciterAPIHost host, SciterEventHandlerMode mode = SciterEventHandlerMode.Element) : base(relatedThing, host, mode)
		{
			var rootContainer = Host.GetElementAttribute(relatedThing, "root-container");
			var templateContainer = Host.GetElementAttribute(relatedThing, "template-container");
			var elementValue = Host.ElementToValue(relatedThing);
			var rootContainerString = Host.CreateValue(rootContainer);
			if (Host.ExecuteWindowFunction(Host.MainWindow, "closestElement", [elementValue, rootContainerString], out var result))
			{
				var rootPointer = Host.ElementFromValue(ref result);
				m_templateContainer = Host.MakeCssSelector(templateContainer, rootPointer).First();
			}

			ParseTree();
		}

		private void ParseTree()
		{
			FillElement(m_templateContainer, 0);

			void FillElement(nint element, int level)
			{
				var countChildrens = Host.GetElementChildrensCount(element);
				for (var i = 0; i < countChildrens; i++)
				{
					var children = Host.GetElementChildren(m_templateContainer, i);
					var name = Host.GetElementAttribute(children, "name");
					var icon = Host.GetElementAttribute(children, "icon");
					var openicon = Host.GetElementAttribute(children, "openicon");
					var index = Host.GetElementAttribute(children, "index");
					var command = Host.GetElementAttribute(children, "command");

					Tree.Add(
						new TreeItemModel
						{
							Command = command,
							Icon = icon,
							Index = Convert.ToInt32(index),
							Level = level,
							Name = name,
							OpenedIcon = openicon
						}
					);

					FillElement(children, level + 1);
				}
			}
		}

		public override EventBehaviourGroups BeforeRegisterEvent()
		{
			return EventBehaviourGroups.HANDLE_MOUSE | EventBehaviourGroups.HANDLE_METHOD_CALL | EventBehaviourGroups.HANDLE_SCRIPTING_METHOD_CALL;
		}

		public override void MouseEvent(MouseEvents command, SciterPoint elementRelated, SciterPoint ViewRelated, KeyboardStates keyboardStates, DraggingType draggingMode, CursorType cursorType, nint target, nint dragging, bool isOnIcon, uint buttonState)
		{
			if (command == MouseEvents.MOUSE_CLICK)
			{
				// show root of items
			}
		}

	}

}
