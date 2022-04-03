using HeuristicLab.PluginInfrastructure;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace HeuristicLab.Algorithms.GeneticAlgorithm.PSP
{
    [Plugin("HeuristicLab.Algorithms.GeneticAlgorithm.PSP", "Provides an implementation of protein structure prediction using genetic algorithms.", "3.3.9.0")]
    [PluginFile("HeuristicLab.Algorithms.GeneticAlgorithm.PSP.dll", PluginFileType.Assembly)]
    [PluginDependency("HeuristicLab.Collections", "3.3")]
    [PluginDependency("HeuristicLab.Common", "3.3")]
    [PluginDependency("HeuristicLab.Core", "3.3")]
    [PluginDependency("HeuristicLab.Data", "3.3")]
    [PluginDependency("HeuristicLab.Operators", "3.3")]
    [PluginDependency("HeuristicLab.Optimization", "3.3")]
    [PluginDependency("HeuristicLab.Optimization.Operators", "3.3")]
    [PluginDependency("HeuristicLab.Random", "3.3")]
    [PluginDependency("HeuristicLab.Parameters", "3.3")]
    [PluginDependency("HeuristicLab.Persistence", "3.3")]
    public class Plugin : PluginBase
    {
    }
}
