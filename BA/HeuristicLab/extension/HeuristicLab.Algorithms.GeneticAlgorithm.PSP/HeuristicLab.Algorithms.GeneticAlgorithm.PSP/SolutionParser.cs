using HeuristicLab.Common;
using HeuristicLab.Core;
using HeuristicLab.Optimization;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace HeuristicLab.Problems.ProteinStructurePrediction
{
    [Item("PSPInstance", "Represents a protein structure prediction instance.")]
    class SolutionParser
    {
        private string file;
        private List<IPSPPEncoding> structures;
        public List<IPSPPEncoding> Structures
        {
            get { return structures; }
        }

        public SolutionParser(string file)
        {
            this.file = file;
            this.structures = new List<IPSPPEncoding>();
        }

        public void Parse()
        {

        }
    }
}
