#region License Information
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

using HeuristicLab.Common;
using HeuristicLab.Core;
using HEAL.Attic;
using HeuristicLab.Problems.DataAnalysis;

namespace HeuristicLab.Algorithms.DataAnalysis {
  /// <summary>
  /// Represents a nearest neighbour solution for a regression problem which can be visualized in the GUI.
  /// </summary>
  [Item("NearestNeighbourRegressionSolution", "Represents a nearest neighbour solution for a regression problem which can be visualized in the GUI.")]
  [StorableType("71C86C1A-C917-4CA4-A239-C167C1C793F8")]
  public sealed class NearestNeighbourRegressionSolution : RegressionSolution, INearestNeighbourRegressionSolution {

    public new INearestNeighbourModel Model {
      get { return (INearestNeighbourModel)base.Model; }
      set { base.Model = value; }
    }

    [StorableConstructor]
    private NearestNeighbourRegressionSolution(StorableConstructorFlag _) : base(_) { }
    private NearestNeighbourRegressionSolution(NearestNeighbourRegressionSolution original, Cloner cloner)
      : base(original, cloner) {
    }
    public NearestNeighbourRegressionSolution(INearestNeighbourModel nnModel, IRegressionProblemData problemData)
      : base(nnModel, problemData) {
    }

    public override IDeepCloneable Clone(Cloner cloner) {
      return new NearestNeighbourRegressionSolution(this, cloner);
    }
  }
}
