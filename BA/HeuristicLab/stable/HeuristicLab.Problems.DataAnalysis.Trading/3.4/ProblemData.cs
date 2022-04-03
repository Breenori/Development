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

using System;
using System.Collections.Generic;
using System.Linq;
using HeuristicLab.Common;
using HeuristicLab.Core;
using HeuristicLab.Data;
using HeuristicLab.Parameters;
using HEAL.Attic;

namespace HeuristicLab.Problems.DataAnalysis.Trading {
  [StorableType("0E535043-BE86-4AF8-8DA1-C82E459F67AB")]
  [Item("TradingProblemData", "Represents an item containing all data defining a trading problem.")]
  public sealed class ProblemData : DataAnalysisProblemData, IProblemData {
    private const string PriceChangeVariableParameterName = "PriceChangeVariable";
    private const string TransactionCostsParameterName = "TransactionCosts";

    #region default data
    private static double[,] audInUsdDiff = new double[,] {
    { 0.0000},
    { 0.0003},
    {-0.0004},
    { 0.0000},
    { 0.0003},
    { 0.0003},
    {-0.0005},
    { 0.0001},
    { 0.0004},
    { 0.0001},
    {-0.0005},
    {-0.0014},
    {-0.0002},
    { 0.0000},
    { 0.0011},
    { 0.0024},
    {-0.0022},
    {-0.0035},
    { 0.0003},
    { 0.0005},
    { 0.0014},
    {-0.0003},
    { 0.0001},
    { 0.0001},
    { 0.0001},
    { 0.0008},
    {-0.0004},
    { 0.0012},
    { 0.0001},
    {-0.0001},
    { 0.0004},
    {-0.0004},
    {-0.0007},
    {-0.0007},
    {-0.0011},
    { 0.0001},
    {-0.0003},
    {-0.0009},
    { 0.0001},
    {-0.0009},
    { 0.0006},
    { 0.0006},
    {-0.0006},
    { 0.0015},
    { 0.0003},
    {-0.0005},
    {-0.0010},
    {-0.0005},
    { 0.0002},
    {-0.0005},
    {-0.0002},
    {-0.0010},
    { 0.0015},
    { 0.0001},
    {-0.0010},
    {-0.0003},
    { 0.0004},
    {-0.0022},
    { 0.0008},
    {-0.0007},
    { 0.0004},
    { 0.0036},
    {-0.0005},
    { 0.0002},
    { 0.0009},
    {-0.0002},
    { 0.0004},
    { 0.0012},
    {-0.0005},
    { 0.0004},
    {-0.0010},
    {-0.0006},
    {-0.0028},
    { 0.0007},
    { 0.0009},
    { 0.0005},
    {-0.0001},
    { 0.0001},
    {-0.0011},
    { 0.0004},
    { 0.0007},
    {-0.0004},
    { 0.0005},
    {-0.0008},
    {-0.0005},
    {-0.0011},
    { 0.0004},
    {-0.0008},
    { 0.0016},
    { 0.0008},
    {-0.0002},
    { 0.0000},
    {-0.0015},
    { 0.0002},
    {-0.0008},
    {-0.0005},
    {-0.0001},
    { 0.0002},
    { 0.0038},
    { 0.0007},
    {-0.0001},
    { 0.0000},
    { 0.0015},
    { 0.0000},
    { 0.0009},
    {-0.0008},
    {-0.0001},
    {-0.0006},
    { 0.0019},
    {-0.0002},
    { 0.0002},
    {-0.0017},
    {-0.0003},
    {-0.0004},
    {-0.0017},
    { 0.0003},
    { 0.0000},
    { 0.0001},
    { 0.0003},
    { 0.0006},
    {-0.0001},
    {-0.0009},
    { 0.0007},
    { 0.0004},
    { 0.0002},
    { 0.0001},
    {-0.0001},
    {-0.0013},
    { 0.0009},
    { 0.0003},
    { 0.0004},
    { 0.0001},
    { 0.0001},
    { 0.0001},
    { 0.0007},
    { 0.0013},
    { 0.0029},
    {-0.0011},
    { 0.0003},
    { 0.0001},
    { 0.0003},
    {-0.0005},
    { 0.0003},
    { 0.0004},
    { 0.0008},
    {-0.0006},
    { 0.0005},
    {-0.0001},
    { 0.0000},
    { 0.0003},
    { 0.0013},
    { 0.0005},
    { 0.0002},
    { 0.0005},
    {-0.0005},
    { 0.0012},
    {-0.0006},
    { 0.0001},
    {-0.0012},
    { 0.0015},
    {-0.0005},
    {-0.0005},
    { 0.0012},
    {-0.0006},
    {-0.0001},
    {-0.0002},
    { 0.0000},
    { 0.0003},
    {-0.0008},
    { 0.0010},
    { 0.0003},
    {-0.0006},
    { 0.0001},
    {-0.0001},
    { 0.0014},
    {-0.0011},
    {-0.0002},
    {-0.0001},
    { 0.0005},
    { 0.0006},
    {-0.0018},
    {-0.0007},
    {-0.0001},
    {-0.0001},
    { 0.0002},
    {-0.0008},
    { 0.0027},
    { 0.0006},
    {-0.0005},
    {-0.0003},
    {-0.0003},
    {-0.0001},
    { 0.0005},
    { 0.0003},
    { 0.0004},
    { 0.0013},
    { 0.0006},
    { 0.0000},
    { 0.0011},
    { 0.0003},
    {-0.0008},
    {-0.0003},
    { 0.0005},
    {-0.0004},
    {-0.0015},
    {-0.0006},
    { 0.0008},
    { 0.0016},
    {-0.0009},
    { 0.0007},
    {-0.0009},
    {-0.0005},
    { 0.0001},
    { 0.0005},
    { 0.0002},
    {-0.0011},
    { 0.0006},
    {-0.0016},
    {-0.0013},
    {-0.0006},
    {-0.0004},
    {-0.0002},
    {-0.0006},
    { 0.0014},
    { 0.0002},
    {-0.0006},
    {-0.0007},
    {-0.0001},
    {-0.0010},
    {-0.0012},
    { 0.0009},
    {-0.0009},
    {-0.0006},
    { 0.0000},
    { 0.0014},
    {-0.0011},
    {-0.0002},
    {-0.0012},
    {-0.0003},
    { 0.0003},
    {-0.0010},
    {-0.0008},
    { 0.0001},
    {-0.0005},
    {-0.0011},
    { 0.0006},
    {-0.0008},
    { 0.0012},
    { 0.0007},
    {-0.0009},
    { 0.0005},
    { 0.0017},
    { 0.0003},
    {-0.0011},
    { 0.0034},
    {-0.0017},
    {-0.0006},
    {-0.0008},
    { 0.0004},
    {-0.0005},
    {-0.0006},
    { 0.0001},
    { 0.0009},
    {-0.0036},
    {-0.0010},
    { 0.0005},
    { 0.0000},
    { 0.0003},
    {-0.0007},
    { 0.0021},
    { 0.0003},
    { 0.0005},
    { 0.0003},
    {-0.0005},
    {-0.0001},
    {-0.0011},
    {-0.0009},
    { 0.0007},
    { 0.0003},
    { 0.0006},
    { 0.0001},
    {-0.0002},
    { 0.0006},
    { 0.0005},
    { 0.0005},
    {-0.0008},
    {-0.0008},
    { 0.0005},
    { 0.0006},
    {-0.0007},
    { 0.0003},
    { 0.0005},
    { 0.0000},
    { 0.0003},
    { 0.0010},
    {-0.0018},
    { 0.0003},
    {-0.0001},
    { 0.0008},
    {-0.0015},
    {-0.0008},
    { 0.0032},
    { 0.0009},
    { 0.0005},
    {-0.0014},
    {-0.0003},
    { 0.0029},
    { 0.0002},
    {-0.0002},
    {-0.0002},
    { 0.0005},
    { 0.0008},
    {-0.0007},
    { 0.0014},
    {-0.0004},
    {-0.0003},
    { 0.0004},
    {-0.0001},
    {-0.0007},
    { 0.0002},
    { 0.0002},
    { 0.0005},
    { 0.0012},
    {-0.0018},
    { 0.0014},
    { 0.0004},
    { 0.0012},
    { 0.0002},
    { 0.0009},
    {-0.0007},
    { 0.0002},
    { 0.0000},
    {-0.0011},
    {-0.0002},
    { 0.0008},
    {-0.0010},
    { 0.0013},
    {-0.0003},
    {-0.0001},
    {-0.0002},
    { 0.0001},
    { 0.0003},
    {-0.0012},
    { 0.0009},
    {-0.0003},
    { 0.0005},
    {-0.0018},
    { 0.0013},
    { 0.0004},
    { 0.0006},
    { 0.0003},
    {-0.0016},
    {-0.0005},
    { 0.0005},
    { 0.0004},
    { 0.0000},
    {-0.0007},
    {-0.0007},
    { 0.0008},
    {-0.0007},
    { 0.0008},
    { 0.0004},
    { 0.0003},
    { 0.0019},
    { 0.0003},
    {-0.0004},
    { 0.0021},
    {-0.0013},
    { 0.0006},
    {-0.0009},
    { 0.0012},
    { 0.0011},
    { 0.0003},
    { 0.0011},
    {-0.0003},
    {-0.0007},
    { 0.0001},
    { 0.0009},
    {-0.0002},
    {-0.0012},
    {-0.0010},
    {-0.0002},
    {-0.0007},
    {-0.0001},
    {-0.0008},
    { 0.0001},
    { 0.0001},
    { 0.0005},
    { 0.0007},
    {-0.0004},
    {-0.0007},
    {-0.0003},
    {-0.0005},
    { 0.0006},
    { 0.0001},
    {-0.0012},
    {-0.0004},
    { 0.0014},
    {-0.0005},
    { 0.0007},
    {-0.0001},
    {-0.0002},
    { 0.0010},
    {-0.0015},
    {-0.0003},
    { 0.0009},
    { 0.0000},
    {-0.0009},
    { 0.0010},
    { 0.0016},
    {-0.0002},
    {-0.0001},
    {-0.0004},
    {-0.0011},
    { 0.0004},
    { 0.0010},
    {-0.0007},
    {-0.0003},
    {-0.0008},
    {-0.0012},
    { 0.0003},
    { 0.0016},
    {-0.0019},
    {-0.0006},
    { 0.0006},
    { 0.0006},
    {-0.0002},
    {-0.0004},
    { 0.0003},
    { 0.0008},
    {-0.0013},
    {-0.0012},
    {-0.0002},
    {-0.0005},
    { 0.0010},
    {-0.0009},
    {-0.0003},
    { 0.0016},
    {-0.0013},
    { 0.0003},
    { 0.0003},
    {-0.0007},
    { 0.0016},
    { 0.0002},
    {-0.0013},
    {-0.0002},
    {-0.0009},
    {-0.0003},
    { 0.0010},
    { 0.0002},
    { 0.0013},
    {-0.0006},
    {-0.0006},
    { 0.0001},
    {-0.0005},
    { 0.0018},
    { 0.0002},
    { 0.0006},
    {-0.0002},
    {-0.0004},
    { 0.0000},
    { 0.0016},
    {-0.0011},
    {-0.0004},
    { 0.0002},
    { 0.0001},
    { 0.0025},
    {-0.0011},
    {-0.0008},
    { 0.0009},
    {-0.0001},
    {-0.0005},
    {-0.0001},
    { 0.0005},
    { 0.0001},
    {-0.0008},
    {-0.0001},
    { 0.0003},
    { 0.0008},
    {-0.0011},
    { 0.0003},
    { 0.0004},
    { 0.0005},
    { 0.0014},
    {-0.0002},
    { 0.0008},
    { 0.0004},
    { 0.0019},
    {-0.0005},
    {-0.0005},
    {-0.0005},
    { 0.0000},
    {-0.0006},
    { 0.0015},
    {-0.0011},
    {-0.0017},
    {-0.0002},
    { 0.0007},
    { 0.0004},
    {-0.0018},
    {-0.0001},
    {-0.0002},
    {-0.0001},
    { 0.0005},
    {-0.0003},
    { 0.0000},
    { 0.0007},
    { 0.0006},
    {-0.0014},
    { 0.0006},
    {-0.0003},
    { 0.0002},
    {-0.0002},
    {-0.0002},
    { 0.0002},
    {-0.0009},
    {-0.0001},
    {-0.0001},
    { 0.0000},
    { 0.0012},
    { 0.0000},
    { 0.0003},
    {-0.0008},
    { 0.0004},
    { 0.0000},
    {-0.0003},
    {-0.0013},
    {-0.0005},
    {-0.0005},
    {-0.0001},
    {-0.0004},
    { 0.0006},
    { 0.0000},
    {-0.0008},
    {-0.0004},
    {-0.0024},
    { 0.0003},
    {-0.0005},
    { 0.0007},
    { 0.0003},
    {-0.0004},
    {-0.0004},
    { 0.0003},
    { 0.0000},
    { 0.0014},
    {-0.0004},
    { 0.0000},
    {-0.0009},
    { 0.0012},
    {-0.0008},
    { 0.0028},
    { 0.0003},
    { 0.0001},
    { 0.0010},
    {-0.0005},
    { 0.0004},
    {-0.0005},
    { 0.0001},
    {-0.0005},
    { 0.0017},
    {-0.0012},
    {-0.0002},
    { 0.0010},
    {-0.0009},
    {-0.0001},
    { 0.0003},
    { 0.0001},
    { 0.0031},
    {-0.0005},
    { 0.0004},
    { 0.0002},
    {-0.0001},
    {-0.0003},
    {-0.0013},
    {-0.0015},
    {-0.0003},
    { 0.0010},
    { 0.0010},
    {-0.0002},
    { 0.0027},
    { 0.0004},
    { 0.0001},
    {-0.0007},
    { 0.0000},
    {-0.0002},
    { 0.0011},
    {-0.0009},
    {-0.0003},
    {-0.0006},
    { 0.0007},
    {-0.0015},
    { 0.0004},
    {-0.0002},
    { 0.0002},
    { 0.0001},
    {-0.0005},
    { 0.0000},
    { 0.0003},
    {-0.0011},
    { 0.0001},
    {-0.0001},
    { 0.0002},
    {-0.0006},
    { 0.0003},
    {-0.0004},
    {-0.0005},
    {-0.0005},
    { 0.0000},
    { 0.0007},
    {-0.0032},
    { 0.0001},
    { 0.0007},
    {-0.0008},
    {-0.0004},
    {-0.0004},
    {-0.0004},
    { 0.0010},
    {-0.0001},
    {-0.0001},
    { 0.0002},
    { 0.0000},
    { 0.0001},
    {-0.0009},
    {-0.0002},
    {-0.0009},
    {-0.0002},
    { 0.0002},
    { 0.0002},
    { 0.0010},
    { 0.0002},
    {-0.0005},
    {-0.0005},
    {-0.0021},
    { 0.0008},
    { 0.0000},
    { 0.0006},
    {-0.0006},
    {-0.0007},
    { 0.0007},
    {-0.0007},
    { 0.0005},
    { 0.0011},
    {-0.0006},
    {-0.0004},
    { 0.0012},
    { 0.0001},
    { 0.0010},
    {-0.0002},
    {-0.0004},
    {-0.0004},
    {-0.0003},
    {-0.0006},
    { 0.0011},
    { 0.0000},
    { 0.0012},
    { 0.0001},
    {-0.0003},
    { 0.0011},
    { 0.0007},
    {-0.0007},
    { 0.0005},
    {-0.0002},
    { 0.0008},
    { 0.0002},
    { 0.0008},
    {-0.0002},
    { 0.0005},
    { 0.0002},
    {-0.0009},
    { 0.0003},
    {-0.0008},
    { 0.0004},
    {-0.0009},
    { 0.0006},
    { 0.0011},
    { 0.0010},
    { 0.0006},
    {-0.0006},
    { 0.0005},
    { 0.0002},
    {-0.0035},
    { 0.0008},
    {-0.0006},
    {-0.0011},
    { 0.0008},
    {-0.0003},
    {-0.0005},
    { 0.0004},
    { 0.0000},
    { 0.0002},
    {-0.0011},
    { 0.0001},
    {-0.0009},
    { 0.0007},
    {-0.0003},
    { 0.0005},
    {-0.0005},
    { 0.0002},
    {-0.0021},
    {-0.0004},
    { 0.0000},
    { 0.0014},
    {-0.0004},
    {-0.0006},
    {-0.0031},
    {-0.0006},
    { 0.0004},
    { 0.0001},
    {-0.0012},
    {-0.0011},
    { 0.0004},
    {-0.0002},
    { 0.0000},
    {-0.0004},
    {-0.0002},
    { 0.0013},
    {-0.0007},
    {-0.0007},
    { 0.0001},
    { 0.0001},
    {-0.0010},
    { 0.0001},
    { 0.0006},
    {-0.0001},
    {-0.0008},
    {-0.0015},
    {-0.0008},
    {-0.0001},
    { 0.0010},
    {-0.0004},
    { 0.0000},
    {-0.0016},
    { 0.0000},
    { 0.0001},
    {-0.0004},
    {-0.0001},
    { 0.0014},
    {-0.0025},
    {-0.0006},
    {-0.0011},
    {-0.0002},
    {-0.0001},
    {-0.0005},
    {-0.0005},
    {-0.0014},
    { 0.0000},
    {-0.0007},
    { 0.0021},
    { 0.0002},
    {-0.0005},
    {-0.0009},
    {-0.0002},
    { 0.0020},
    { 0.0004},
    {-0.0011},
    {-0.0018},
    { 0.0005},
    { 0.0005},
    { 0.0000},
    { 0.0000},
    { 0.0004},
    { 0.0008},
    {-0.0004},
    {-0.0007},
    { 0.0001},
    { 0.0009},
    {-0.0001},
    { 0.0010},
    {-0.0005},
    {-0.0023},
    { 0.0004},
    { 0.0022},
    {-0.0013},
    { 0.0003},
    {-0.0003},
    {-0.0003},
    { 0.0010},
    {-0.0002},
    { 0.0000},
    { 0.0002},
    {-0.0004},
    {-0.0007},
    {-0.0005},
    {-0.0003},
    { 0.0005},
    {-0.0010},
    {-0.0004},
    { 0.0001},
    { 0.0003},
    { 0.0000},
    { 0.0008},
    { 0.0001},
    { 0.0004},
    { 0.0002},
    { 0.0001},
    {-0.0005},
    {-0.0005},
    {-0.0003},
    { 0.0016},
    { 0.0006},
    {-0.0014},
    { 0.0016},
    { 0.0016},
    { 0.0009},
    {-0.0002},
    {-0.0002},
    { 0.0005},
    {-0.0005},
    {-0.0004},
    {-0.0008},
    {-0.0003},
    {-0.0001},
    { 0.0005},
    {-0.0002},
    {-0.0004},
    {-0.0003},
    { 0.0003},
    { 0.0003},
    {-0.0003},
    { 0.0003},
    {-0.0004},
    { 0.0000},
    {-0.0008},
    {-0.0013},
    { 0.0007},
    {-0.0011},
    { 0.0015},
    {-0.0008},
    { 0.0007},
    {-0.0002},
    {-0.0004},
    { 0.0005},
    {-0.0008},
    { 0.0000},
    {-0.0008},
    { 0.0007},
    { 0.0007},
    { 0.0011},
    { 0.0000},
    { 0.0003},
    {-0.0005},
    { 0.0003},
    { 0.0012},
    { 0.0005},
    {-0.0006},
    {-0.0002},
    {-0.0007},
    {-0.0027},
    {-0.0012},
    {-0.0005},
    { 0.0005},
    { 0.0002},
    { 0.0001},
    { 0.0003},
    { 0.0003},
    { 0.0002},
    {-0.0002},
    {-0.0003},
    { 0.0009},
    { 0.0003},
    { 0.0003},
    { 0.0006},
    {-0.0002},
    {-0.0003},
    {-0.0004},
    { 0.0011},
    { 0.0000},
    { 0.0000},
    { 0.0000},
    {-0.0007},
    { 0.0001},
    { 0.0019},
    { 0.0011},
    {-0.0011},
    { 0.0002},
    { 0.0009},
    { 0.0002},
    { 0.0004},
    {-0.0001},
    {-0.0008},
    { 0.0001},
    { 0.0003},
    {-0.0002},
    {-0.0002},
    { 0.0002},
    { 0.0003},
    { 0.0000},
    { 0.0010},
    { 0.0013},
    {-0.0004},
    {-0.0009},
    {-0.0005},
    { 0.0018},
    { 0.0018},
    {-0.0006},
    {-0.0006},
    {-0.0009},
    { 0.0005},
    {-0.0004},
    {-0.0001},
    { 0.0012},
    {-0.0002},
    {-0.0006},
    {-0.0024},
    {-0.0002},
    {-0.0011},
    { 0.0003},
    { 0.0009},
    { 0.0002},
    { 0.0002},
    { 0.0003},
    {-0.0002},
    {-0.0002},
    { 0.0000},
    { 0.0000},
    {-0.0010},
    {-0.0007},
    { 0.0009},
    { 0.0001},
    { 0.0020},
    { 0.0001},
    { 0.0005},
    {-0.0003},
    { 0.0004},
    {-0.0005},
    { 0.0005},
    { 0.0002},
    { 0.0001},
    { 0.0001},
    { 0.0004},
    { 0.0008},
    { 0.0000},
    {-0.0008},
    { 0.0002},
    {-0.0012},
    {-0.0004},
    { 0.0004},
    {-0.0001},
    { 0.0010},
    {-0.0009},
    {-0.0007},
    {-0.0006},
    {-0.0002},
    { 0.0001},
    {-0.0004},
    { 0.0002},
    { 0.0000},
    { 0.0000},
    {-0.0012},
    {-0.0002},
    {-0.0002},
    { 0.0009},
    {-0.0008},
    {-0.0001},
    { 0.0008},
    {-0.0001},
    {-0.0002},
    {-0.0004},
    { 0.0009},
    { 0.0001},
    { 0.0005},
    { 0.0015},
    {-0.0001},
    {-0.0002},
    {-0.0004},
    { 0.0009},
    {-0.0010},
    {-0.0005},
    { 0.0004},
    { 0.0011},
    { 0.0009},
    {-0.0003},
    {-0.0002},
    { 0.0006},
    { 0.0003},
    {-0.0003},
    {-0.0002},
    { 0.0015},
    { 0.0003},
    { 0.0001},
    {-0.0001},
    {-0.0001},
    {-0.0005},
    {-0.0001},
    { 0.0003},
    { 0.0002},
    { 0.0001},
    {-0.0002},
    {-0.0008},
    { 0.0003},
    {-0.0001},
    { 0.0000},
    { 0.0002},
    {-0.0002},
    {-0.0001},
    {-0.0005},
    { 0.0002},
    { 0.0000},
    { 0.0000},
    { 0.0004},
    { 0.0000},
    {-0.0013},
    {-0.0043},
    { 0.0007},
    { 0.0001},
    {-0.0007},
    {-0.0001},
    { 0.0003},
    { 0.0013},
    { 0.0005},
    {-0.0007},
    { 0.0002},
    {-0.0014},
    {-0.0002},
    { 0.0000},
    { 0.0020},
    { 0.0009},
    {-0.0018},
    {-0.0005},
    {-0.0009},
    {-0.0005},
    { 0.0008},
    { 0.0005},
    {-0.0004},
    { 0.0004},
    { 0.0001},
    { 0.0003},
    { 0.0003},
    {-0.0008},
    {-0.0007},
    { 0.0008},
    {-0.0004},
    {-0.0028},
    {-0.0006},
    {-0.0022},
    {-0.0009},
    { 0.0003},
    { 0.0003},
    { 0.0000},
    { 0.0021},
    {-0.0017},
    { 0.0009},
    {-0.0001},
    {-0.0005},
    {-0.0015},
    { 0.0009},
    { 0.0009},
    {-0.0009},
    { 0.0010},
    { 0.0000},
    { 0.0018},
    {-0.0011},
    { 0.0001},
    {-0.0008},
    { 0.0009},
    { 0.0022},
    { 0.0011},
    {-0.0002},
    {-0.0018},
    { 0.0019},
    {-0.0004},
    {-0.0004},
    { 0.0002},
    { 0.0027},
    {-0.0012},
    {-0.0003},
    {-0.0002},
    { 0.0013},
    { 0.0002},
    {-0.0003},
    { 0.0002},
    { 0.0003},
    {-0.0002},
    { 0.0020},
    {-0.0003},
    { 0.0002},
    {-0.0001},
    {-0.0001},
    { 0.0006},
    {-0.0012},
    { 0.0011},
    { 0.0001},
    { 0.0001},
    { 0.0004},
    {-0.0002},
    { 0.0029},
    {-0.0016},
    { 0.0005},
    {-0.0029},
    {-0.0002},
    { 0.0013},
    { 0.0011},
    {-0.0003},
    { 0.0002},
    { 0.0001},
    { 0.0001},
    {-0.0005},
    { 0.0000},
    { 0.0009},
    { 0.0016},
    { 0.0005},
    { 0.0003},
    { 0.0004},
    {-0.0001},
    { 0.0020},
    { 0.0006},
    {-0.0006},
    {-0.0004},
    { 0.0012},
    { 0.0012},
    { 0.0017},
    { 0.0017},
    {-0.0004},
    { 0.0001},
    { 0.0001},
    {-0.0006},
    {-0.0003},
    { 0.0004},
    { 0.0008},
    {-0.0014},
    { 0.0011},
    {-0.0003},
    { 0.0004},
    {-0.0001},
    { 0.0017},
    { 0.0008},
    { 0.0005},
    {-0.0002},
    { 0.0001},
    {-0.0013},
    { 0.0009},
    {-0.0008},
    {-0.0003},
    { 0.0013},
    {-0.0002},
    {-0.0004},
    { 0.0007},
    {-0.0009},
    { 0.0002},
    {-0.0002},
    {-0.0006},
    { 0.0003},
    {-0.0003},
    {-0.0004},
    {-0.0006},
    {-0.0004},
    { 0.0006},
    {-0.0006},
    { 0.0019},
    {-0.0012},
    {-0.0002},
    { 0.0003},
    { 0.0001},
    { 0.0001},
    { 0.0002},
    { 0.0004},
    { 0.0000},
    {-0.0013},
    {-0.0017},
    {-0.0017},
    {-0.0006},
    {-0.0003},
    { 0.0006},
    { 0.0001},
    { 0.0007},
    {-0.0004},
    { 0.0000},
    { 0.0019},
    {-0.0008},
    {-0.0006},
    { 0.0003},
    {-0.0004},
    {-0.0002},
    { 0.0008},
    {-0.0007},
    {-0.0004},
    {-0.0001},
    {-0.0004},
    {-0.0003},
    { 0.0004},
    {-0.0008},
    { 0.0015},
    { 0.0011},
    {-0.0013},
    {-0.0003},
    { 0.0000},
    { 0.0006},
    {-0.0003},
    {-0.0003},
    { 0.0005},
    {-0.0016},
    { 0.0005},
    {-0.0002},
    {-0.0009},
    {-0.0001},
    {-0.0004},
    { 0.0007},
    { 0.0004},
    { 0.0015},
    { 0.0005},
    {-0.0007},
    { 0.0002},
    {-0.0007},
    {-0.0009},
    {-0.0029},
    { 0.0003},
    {-0.0002},
    {-0.0010},
    {-0.0001},
    { 0.0005},
    {-0.0003},
    { 0.0002},
    {-0.0006},
    { 0.0008},
    {-0.0010},
    { 0.0005},
    { 0.0003},
    { 0.0009},
    { 0.0002},
    { 0.0001},
    { 0.0002},
    {-0.0010},
    {-0.0017},
    { 0.0004},
    {-0.0007},
    { 0.0019},
    {-0.0001},
    {-0.0004},
    {-0.0023},
    { 0.0015},
    { 0.0009},
    {-0.0006},
    {-0.0001},
    { 0.0000},
    { 0.0001},
    { 0.0003},
    {-0.0002},
    { 0.0039},
    {-0.0007},
    { 0.0000},
    {-0.0002},
    {-0.0005},
    { 0.0007},
    { 0.0010},
    {-0.0004},
    { 0.0006},
    {-0.0003},
    {-0.0006},
    { 0.0003},
    { 0.0022},
    {-0.0030},
    { 0.0010},
    { 0.0005},
    { 0.0000},
    {-0.0005},
    {-0.0004},
    {-0.0010},
    {-0.0001},
    { 0.0000},
    {-0.0002},
    { 0.0003},
    {-0.0003},
    {-0.0007},
    {-0.0001},
    { 0.0016},
    {-0.0009},
    { 0.0001},
    { 0.0005},
    { 0.0016},
    {-0.0013},
    {-0.0003},
    {-0.0002},
    { 0.0014},
    {-0.0008},
    { 0.0026},
    {-0.0003},
    { 0.0007},
    { 0.0011},
    { 0.0005},
    {-0.0001},
    { 0.0004},
    {-0.0003},
    { 0.0006},
    {-0.0013},
    { 0.0002},
    {-0.0003},
    {-0.0010},
    { 0.0000},
    {-0.0007},
    {-0.0001},
    { 0.0008},
    {-0.0010},
    {-0.0005},
    { 0.0010},
    { 0.0013},
    { 0.0008},
    {-0.0004},
    { 0.0020},
    {-0.0002},
    { 0.0005},
    { 0.0003},
    { 0.0004},
    { 0.0005},
    { 0.0007},
    {-0.0008},
    { 0.0003},
    {-0.0008},
    { 0.0011},
    { 0.0005},
    { 0.0002},
    {-0.0005},
    {-0.0011},
    { 0.0001},
    {-0.0002},
    {-0.0003},
    { 0.0016},
    {-0.0005},
    {-0.0002},
    {-0.0008},
    { 0.0023},
    { 0.0015},
    { 0.0001},
    {-0.0004},
    { 0.0015},
    {-0.0002},
    { 0.0003},
    { 0.0001},
    { 0.0002},
    {-0.0007},
    { 0.0005},
    {-0.0001},
    { 0.0007},
    {-0.0007},
    { 0.0018},
    {-0.0002},
    { 0.0005},
    {-0.0002},
    {-0.0004},
    {-0.0001},
    {-0.0001},
    { 0.0002},
    { 0.0009},
    { 0.0003},
    {-0.0006},
    {-0.0003},
    {-0.0022},
    { 0.0002},
    { 0.0004},
    { 0.0004},
    {-0.0005},
    {-0.0008},
    {-0.0001},
    { 0.0000},
    { 0.0010},
    { 0.0001},
    {-0.0005},
    {-0.0003},
    {-0.0005},
    { 0.0005},
    {-0.0003},
    { 0.0000},
    { 0.0002},
    { 0.0001},
    {-0.0014},
    {-0.0005},
    {-0.0001},
    { 0.0006},
    { 0.0004},
    { 0.0005},
    { 0.0017},
    { 0.0009},
    { 0.0008},
    { 0.0017},
    { 0.0006},
    {-0.0003},
    { 0.0004},
    { 0.0000},
    {-0.0015},
    {-0.0001},
    { 0.0000},
    {-0.0008},
    { 0.0000},
    { 0.0004},
    {-0.0006},
    { 0.0001},
    { 0.0001},
    { 0.0003},
    {-0.0001},
    { 0.0001},
    {-0.0011},
    {-0.0011},
    { 0.0010},
    { 0.0004},
    { 0.0008},
    { 0.0007},
    { 0.0004},
    {-0.0023},
    { 0.0023},
    {-0.0001},
    {-0.0004},
    { 0.0000},
    {-0.0003},
    {-0.0008},
    { 0.0005},
    { 0.0004},
    {-0.0004},
    { 0.0001},
    {-0.0007},
    {-0.0001},
    {-0.0006},
    {-0.0012},
    {-0.0027},
    { 0.0002},
    {-0.0012},
    { 0.0013},
    { 0.0000},
    {-0.0008},
    { 0.0009},
    {-0.0015},
    { 0.0007},
    { 0.0002},
    { 0.0001},
    {-0.0013},
    { 0.0002},
    {-0.0004},
    {-0.0002},
    {-0.0027},
    { 0.0013},
    {-0.0005},
    { 0.0006},
    { 0.0000},
    {-0.0005},
    { 0.0011},
    { 0.0000},
    {-0.0003},
    { 0.0018},
    {-0.0003},
    { 0.0006},
    {-0.0008},
    {-0.0006},
    {-0.0015},
    {-0.0009},
    {-0.0017},
    { 0.0005},
    { 0.0007},
    {-0.0006},
    {-0.0004},
    { 0.0016},
    { 0.0000},
    { 0.0003},
    {-0.0019},
    { 0.0003},
    { 0.0005},
    { 0.0003},
    { 0.0001},
    {-0.0002},
    { 0.0007},
    { 0.0001},
    {-0.0012},
    { 0.0008},
    {-0.0011},
    { 0.0008},
    { 0.0010},
    {-0.0003},
    {-0.0003},
    {-0.0006},
    {-0.0004},
    { 0.0000},
    { 0.0011},
    { 0.0003},
    {-0.0005},
    {-0.0002},
    { 0.0001},
    {-0.0004},
    { 0.0008},
    {-0.0007},
    {-0.0005},
    {-0.0005},
    {-0.0003},
    {-0.0005},
    { 0.0006},
    {-0.0014},
    {-0.0001},
    { 0.0003},
    { 0.0009},
    { 0.0012},
    {-0.0023},
    {-0.0004},
    { 0.0002},
    { 0.0001},
    {-0.0019},
    { 0.0012},
    {-0.0022},
    { 0.0001},
    {-0.0004},
    {-0.0001},
    { 0.0012},
    { 0.0001},
    { 0.0000},
    { 0.0004},
    {-0.0008},
    { 0.0006},
    {-0.0007},
    { 0.0008},
    {-0.0009},
    {-0.0005},
    {-0.0001},
    {-0.0004},
    { 0.0001},
    {-0.0005},
    {-0.0004},
    {-0.0012},
    { 0.0002},
    { 0.0011},
    { 0.0008},
    {-0.0009},
    { 0.0010},
    {-0.0003},
    {-0.0006},
    { 0.0005},
    { 0.0002},
    {-0.0003},
    { 0.0016},
    {-0.0006},
    { 0.0000},
    { 0.0008},
    {-0.0002},
    { 0.0000},
    { 0.0000},
    { 0.0003},
    {-0.0011},
    {-0.0009},
    {-0.0013},
    {-0.0003},
    { 0.0009},
    { 0.0007},
    {-0.0005},
    { 0.0012},
    {-0.0009},
    { 0.0004},
    {-0.0008},
    {-0.0011},
    { 0.0013},
    { 0.0013},
    { 0.0005 }};

    private static Dataset defaultDataset;
    private static IEnumerable<string> defaultAllowedInputVariables;
    private static string defaultPriceVariable;

    static ProblemData() {
      defaultDataset = new Dataset(new string[] { "d(AUD/USD)/dt" }, audInUsdDiff);
      defaultDataset.Name = "AUD in USD";
      defaultDataset.Description = "Australian dollar in US dollar.";
      defaultAllowedInputVariables = new List<string>() { "d(AUD/USD)/dt" };
      defaultPriceVariable = "d(AUD/USD)/dt";
    }
    #endregion

    public IConstrainedValueParameter<StringValue> PriceChangeVariableParameter {
      get { return (IConstrainedValueParameter<StringValue>)Parameters[PriceChangeVariableParameterName]; }
    }
    public IValueParameter<DoubleValue> TransactionCostsParameter {
      get { return (IValueParameter<DoubleValue>)Parameters[TransactionCostsParameterName]; }
    }
    public string PriceChangeVariable {
      get { return PriceChangeVariableParameter.Value.Value; }
    }
    public double TransactionCosts {
      get { return TransactionCostsParameter.Value.Value; }
    }

    [StorableConstructor]
    private ProblemData(StorableConstructorFlag _) : base(_) { }
    [StorableHook(HookType.AfterDeserialization)]
    private void AfterDeserialization() {
      RegisterParameterEvents();
    }

    private ProblemData(ProblemData original, Cloner cloner)
      : base(original, cloner) {
      RegisterParameterEvents();
    }
    public override IDeepCloneable Clone(Cloner cloner) { return new ProblemData(this, cloner); }

    public ProblemData()
      : this(defaultDataset, defaultAllowedInputVariables, defaultPriceVariable) {
    }

    public ProblemData(Dataset dataset, IEnumerable<string> allowedInputVariables, string targetVariable, IEnumerable<ITransformation> transformations = null)
      : base(dataset, allowedInputVariables, transformations ?? Enumerable.Empty<ITransformation>()) {
      var variables = InputVariables.Select(x => x.AsReadOnly()).ToList();
      Parameters.Add(new ConstrainedValueParameter<StringValue>(PriceChangeVariableParameterName, new ItemSet<StringValue>(variables), variables.First(x => x.Value == targetVariable)));
      Parameters.Add(new FixedValueParameter<DoubleValue>(TransactionCostsParameterName, "The absolute cost of on buy/sell transaction (assumed to be constant and independent of transaction volume)", new DoubleValue(0.0002)));

      if (dataset.GetReadOnlyDoubleValues(targetVariable).Min() >= 0) throw new ArgumentException("The target variable must contain changes (deltas) of the asset price over time.");

      RegisterParameterEvents();
    }

    private void RegisterParameterEvents() {
      PriceChangeVariableParameter.ValueChanged += new EventHandler(PriceVariableParameter_ValueChanged);
      TransactionCostsParameter.Value.ValueChanged += new EventHandler(TransactionCostsParameter_ValueChanged);
    }

    private void TransactionCostsParameter_ValueChanged(object sender, EventArgs e) {
      OnChanged();
    }
    private void PriceVariableParameter_ValueChanged(object sender, EventArgs e) {
      if (Dataset.GetReadOnlyDoubleValues(PriceChangeVariable).Min() >= 0) throw new ArgumentException("The target variable must contain changes (deltas) of the asset price over time.");
      OnChanged();
    }
  }
}
