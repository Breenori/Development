using HEAL.Attic;
using HeuristicLab.Common;
using HeuristicLab.Core;
using HeuristicLab.Problems.ProteinStructurePrediction.Interfaces;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace HeuristicLab.Problems.ProteinStructurePrediction
{
    public class ProteinStructure : Item 
    {
        [Storable]
        public string Sequence { get; private set; }

        [Storable]
        public List<double> Phi { get; private set; }
        [Storable]
        public List<double> Psi { get; private set; }

        public override IDeepCloneable Clone(Cloner cloner)
        {
            return new ProteinStructure(this, cloner);
        }

        protected ProteinStructure(ProteinStructure original, Cloner cloner) : base(original, cloner)
        {
            this.Sequence = original.Sequence;
            this.Phi = new List<double>(original.Phi);
            this.Psi = new List<double>(original.Psi);
        }

        [StorableConstructor]
        protected ProteinStructure(StorableConstructorFlag _) : base(_) { }

        public List<Tuple<double,double,double>> GetCartesianCoordinates(IPSPProblemInstance instance, IPSPPEncoding solution)
        {
            List<Tuple<double, double, double>> coords = new List<Tuple<double, double, double>>();
            
            for 
        }
    }
}
