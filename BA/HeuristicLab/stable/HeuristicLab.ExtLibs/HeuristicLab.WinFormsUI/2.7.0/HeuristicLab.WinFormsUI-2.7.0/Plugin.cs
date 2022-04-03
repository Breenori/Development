﻿#region License Information
/* HeuristicLab
 * Copyright (C) Heuristic and Evolutionary Algorithms Laboratory (HEAL)
 *
 * This file is part of HeuristicLab.
 *
 * HeuristicLab is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * HeuristicLab is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with HeuristicLab. If not, see <http://www.gnu.org/licenses/>.
 */
#endregion

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using HeuristicLab.PluginInfrastructure;

namespace HeuristicLab.WinFormsUI {
  [Plugin("HeuristicLab.WinFormsUI", "2.7.0.17181")]
  [PluginFile("HeuristicLab.WinFormsUI-2.7.0.dll", PluginFileType.Assembly)]
  [PluginFile("WeifenLuo.WinFormsUI.Docking-2.7.0.dll", PluginFileType.Assembly)]
  [PluginFile("WeifenLuo.WinFormsUI.Docking License-2.7.0.txt",PluginFileType.License)]
  public class HeuristicLabWinFormsUIPlugin : PluginBase {
  }
}
