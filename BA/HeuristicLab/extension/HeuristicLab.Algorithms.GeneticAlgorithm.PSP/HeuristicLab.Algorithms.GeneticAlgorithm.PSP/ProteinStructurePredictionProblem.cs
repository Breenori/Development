using HEAL.Attic;
using HeuristicLab.Algorithms.GeneticAlgorithm.PSP.Interfaces;
using HeuristicLab.Common;
using HeuristicLab.Core;
using HeuristicLab.Data;
using HeuristicLab.Optimization;
using HeuristicLab.Optimization.Operators;
using HeuristicLab.Parameters;
using HeuristicLab.PluginInfrastructure;
using HeuristicLab.Problems.Instances;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace HeuristicLab.Problems.ProteinStructurePredictionProblem
{
    [Item("Protein Structure Prediction Problem (PSPP)", "Represents a Protein Structure Prediction Problem.")]
    [Creatable(CreatableAttribute.Categories.CombinatorialProblems, Priority = 110)]
    [StorableType("95137523-AE3B-4638-958C-E86829D54CE4")]
    public sealed class ProteinStructurePredictionProblem : Problem, ISingleObjectiveHeuristicOptimizationProblem, IStorableContent, IProblemInstanceConsumer<VRPData>
    {
        public string Filename { get; set; }

        #region Parameters
        public ValueParameter<BoolValue> MaximizationParameter
        {
            get { return (ValueParameter<BoolValue>)Parameters["Maximization"]; }
        }
        IParameter ISingleObjectiveHeuristicOptimizationProblem.MaximizationParameter
        {
            get { return MaximizationParameter; }
        }

        public ValueParameter<IPSPProblemInstance> ProblemInstanceParameter
        {
            get { return (ValueParameter<IPSPProblemInstance>)Parameters["ProblemInstance"]; }
        }

        public OptionalValueParameter<DoubleValue> BestKnownQualityParameter
        {
            get { return (OptionalValueParameter<DoubleValue>)Parameters["BestKnownQuality"]; }
        }
        IParameter ISingleObjectiveHeuristicOptimizationProblem.BestKnownQualityParameter
        {
            get { return BestKnownQualityParameter; }
        }

        public OptionalValueParameter<PSPPSolution> BestKnownSolutionParameter
        {
            get { return (OptionalValueParameter<PSPPSolution>)Parameters["BestKnownSolution"]; }
        }
        public IConstrainedValueParameter<IPSPPCreator> SolutionCreatorParameter
        {
            get { return (IConstrainedValueParameter<IPSPCreator>)Parameters["SolutionCreator"];  }
        }
        IParameter IHeuristicOptimizationProblem.SolutionCreatorParameter
        {
            get { return SolutionCreatorParameter; }
        }

        public IValueParameter<IPSPPEvaluator> EvaluatorParameter
        {
            get { return (IValueParameter<IPSPEvaluator>)Parameters["Evaluator"]; }
        }
        IParameter IHeuristicOptimizationProblem.EvaluatorParameter
        {
            get { return EvaluatorParameter; }
        }


        #endregion

        #region Properties
        public IPSPProblemInstance ProblemInstance
        {
            get { return ProblemInstanceParameter.Value; }
            set { ProblemInstanceParameter.Value = value; }
        }

        public PSPPSolution BestKnownSolution
        {
            get { return BestKnownSolutionParameter.Value; }
            set { BestKnownSolutionParameter.Value = value; }
        }

        public DoubleValue BestKnownQuality
        {
            get { return BestKnownQualityParameter.Value; }
            set { BestKnownQualityParameter.Value = value; }
        }

        public ISolutionCreator SolutionCreator
        {
            get { return SolutionCreatorParameter.Value; }
        }

        public ISingleObjectiveEvaluator Evaluator
        {
            get { return EvaluatorParameter.Value; }
        }
        IEvaluator IHeuristicOptimizationProblem.Evaluator
        {
            get { return this.Evaluator; }
        }
        #endregion

        [StorableConstructor]
        private ProteinStructurePredictionProblem(StorableConstructorFlag _) : base(_) { }
        public ProteinStructurePredictionProblem() : base()
        {
            Parameters.Add(new ValueParameter<BoolValue>("Maximization", "Set to false as the Vehicle Routing Problem is a minimization problem.", new BoolValue(false)));
            Parameters.Add(new ValueParameter<IPSPProblemInstance>("ProblemInstance", "The VRP problem instance"));
            Parameters.Add(new OptionalValueParameter<DoubleValue>("BestKnownQuality", "The quality of the best known solution of this VRP instance."));
            Parameters.Add(new OptionalValueParameter<PSPPSolution>("BestKnownSolution", "The best known solution of this VRP instance."));

            Parameters.Add(new ConstrainedValueParameter<IPSPPCreator>("SolutionCreator", "The operator which should be used to create new VRP solutions."));
            Parameters.Add(new ValueParameter<IPSPPEvaluator>("Evaluator", "The operator which should be used to evaluate VRP solutions."));

            EvaluatorParameter.Hidden = true;

            InitializeRandomPSPInstance();
            InitializeOperators();

            AttachEventHandlers();
            AttachProblemInstanceEventHandlers();

            EvaluatorParameter.Value = ProblemInstance.SolutionEvaluator;
        }

        public override IDeepCloneable Clone(Cloner cloner)
        {
            throw new NotImplementedException();
        }

        private ProteinStructurePredictionProblem(ProteinStructurePredictionProblem original, Cloner cloner) : base(original, cloner)
        {
            this.AttachEventHandlers();
            this.AttachProblemInstanceEventHandlers();

            ProblemInstance.SolutionEvaluator = EvaluatorParamter.Value;
        }

        #region Events
        public event EventHandler SolutionCreatorChanged;
        private void OnSolutionCreatorChanged()
        {
            EventHandler handler = SolutionCreatorChanged;
            if (handler != null) handler(this, EventArgs.Empty);
        }

        public event EventHandler EvaluatorChanged;
        private void OnEvaluatorChanged()
        {
            EventHandler handler = EvaluatorChanged;
            if (handler != null) handler(this, EventArgs.Empty);
        }

        #endregion

        #region Helpers
        [StorableHook(HookType.AfterDeserialization)]
        private void AfterDeserialization()
        {
            AttachEventHandlers();
            AttachProblemInstanceEventhandlers();

            ProblemInstance.SolutionEvaluator = EvaluatorParameter.Value;
        }

        [Storable(OldName = "operators")]
        private List<IOperator> StorableOperators
        {
            set { Operators.AddRange(value); }
        }

        private void AttachEventHandlers()
        {
            ProblemInstanceParameter.ValueChanged += new EventHandler(ProblemInstanceParameter_ValueChanged);
            BestKnownSolutionParameter.ValueChanged += new EventHandler(BestKnownSolutionParameter_ValueChanged);
            EvaluatorParameter.ValueChanged += new EventHandler(EvaluatorParameter_ValueChanged);
            SolutionCreatorParameter.ValueChanged += new EventHandler(SolutionCreatorParameter_ValueChanged);
        }

        private void AttachProblemInstanceEventHandlers()
        {
            if (ProblemInstance != null)
            {
                ProblemInstance.EvaluationChanged += new EventHandler(ProblemInstance_EvaluationChanged);
            }
        }

        private void EvalBestKnownSolution()
        {
            if (BestKnownSolution == null) return;
            try
            {
                //call evaluator
                BestKnownQuality = new DoubleValue(ProblemInstance.Evaluate(BestKnownSolution.Solution).Quality);
                BestKnownSolution.Quality = BestKnownQuality;
            }
            catch
            {
                BestKnownQuality = null;
                BestKnownSolution = null;
            }
        }

        void BestKnownSolutionParameter_ValueChanged(object sender, EventArgs e)
        {
            EvalBestKnownSolution();
        }

        void ProblemInstance_EvaluationChanged(object sender, EventArgs e)
        {
            BestKnownQuality = null;
            if (BestKnownSolution != null)
            {
                // TODO: 

                // the tour is not valid if there are more vehicles in it than allowed
                if (ProblemInstance.Vehicles.Value < BestKnownSolution.Solution.GetTours().Count)
                {
                    BestKnownSolution = null;
                }
                else EvalBestKnownSolution();
            }
        }

        void ProblemInstanceParameter_ValueChanged(object sender, EventArgs e)
        {
            InitializeOperators();
            AttachProblemInstanceEventHandlers();

            EvaluatorParameter.Value = ProblemInstance.SolutionEvaluator;

            OnSolutionCreatorChanged();
            OnEvaluatorChanged();
            OnOperatorsChanged();
        }

        public void SetProblemInstance(IPSPProblemInstance instance)
        {
            ProblemInstanceParameter.ValueChanged -= new EventHandler(ProblemInstanceParameter_ValueChanged);

            ProblemInstance = instance;
            AttachProblemInstanceEventHandlers();

            OnSolutionCreatorChanged();
            OnEvaluatorChanged();

            ProblemInstanceParameter.ValueChanged += new EventHandler(ProblemInstanceParameter_ValueChanged);
        }

        private void SolutionCreatorParameter_ValueChanged(object sender, EventArgs e)
        {
            OnSolutionCreatorChanged();
        }
        private void EvaluatorParameter_ValueChanged(object sender, EventArgs e)
        {
            if (ProblemInstance != null)
                ProblemInstance.SolutionEvaluator = EvaluatorParameter.Value;
            OnEvaluatorChanged();
        }

        private void InitializeOperators()
        {
            var solutionCreatorParameter = SolutionCreatorParameter as ConstrainedValueParameter<IPSPPCreator>;
            solutionCreatorParameter.ValidValues.Clear();

            Operators.Clear();

            if (ProblemInstance != null)
            {
                Operators.AddRange(
                ProblemInstance.Operators.Concat(
                  ApplicationManager.Manager.GetInstances<IGeneralPSPPOperator>().Cast<IOperator>()).OrderBy(op => op.Name));
                Operators.Add(new PSPPSimilarityCalculator());
                Operators.Add(new QualitySimilarityCalculator());
                Operators.Add(new PopulationSimilarityAnalyzer(Operators.OfType<ISolutionSimilarityCalculator>()));


                //TODO: FIX
                IPSPPCreator defaultCreator = null;
                foreach (IPSPPCreator creator in Operators.Where(o => o is IPSPPCreator))
                {
                    solutionCreatorParameter.ValidValues.Add(creator);
                    if (creator is Encodings.Alba.RandomCreator)
                        defaultCreator = creator;
                }
                Operators.Add(new AlbaLambdaInterchangeLocalImprovementOperator());
                if (defaultCreator != null)
                    solutionCreatorParameter.Value = defaultCreator;
            }

            ParameterizeOperators();
        }

        private void ParameterizeOperators()
        {
            foreach (IOperator op in Operators.OfType<IOperator>())
            {
                if (op is IMultiPSPPOperator)
                {
                    (op as IMultiPSPPOperator).SetOperators(Operators.OfType<IOperator>());
                }
            }
            if (ProblemInstance != null)
            {
                foreach (ISingleObjectiveImprovementOperator op in Operators.OfType<ISingleObjectiveImprovementOperator>())
                {
                    op.SolutionParameter.ActualName = SolutionCreator.VRPToursParameter.ActualName;
                    op.SolutionParameter.Hidden = true;
                }
                foreach (ISingleObjectivePathRelinker op in Operators.OfType<ISingleObjectivePathRelinker>())
                {
                    op.ParentsParameter.ActualName = SolutionCreator.VRPToursParameter.ActualName;
                    op.ParentsParameter.Hidden = true;
                }
                foreach (ISolutionSimilarityCalculator op in Operators.OfType<ISolutionSimilarityCalculator>())
                {
                    op.SolutionVariableName = SolutionCreator.VRPToursParameter.ActualName;
                    op.QualityVariableName = ProblemInstance.SolutionEvaluator.QualityParameter.ActualName;
                    var calc = op as PSPPSimilarityCalculator;
                    if (calc != null) calc.ProblemInstance = ProblemInstance;
                }
            }
        }
        #endregion

        private void InitializeRandomPSPPInstance()
        {
            System.Random rand = new System.Random();

            PSPProblemInstance problem = new PSPProblemInstance();
            int cities = 100;

            problem.Coordinates = new DoubleMatrix(cities + 1, 2);
            problem.Demand = new DoubleArray(cities + 1);
            problem.DueTime = new DoubleArray(cities + 1);
            problem.ReadyTime = new DoubleArray(cities + 1);
            problem.ServiceTime = new DoubleArray(cities + 1);

            problem.Vehicles.Value = 100;
            problem.Capacity.Value = 200;

            for (int i = 0; i <= cities; i++)
            {
                problem.Coordinates[i, 0] = rand.Next(0, 100);
                problem.Coordinates[i, 1] = rand.Next(0, 100);

                if (i == 0)
                {
                    problem.Demand[i] = 0;
                    problem.DueTime[i] = Int16.MaxValue;
                    problem.ReadyTime[i] = 0;
                    problem.ServiceTime[i] = 0;
                }
                else
                {
                    problem.Demand[i] = rand.Next(10, 50);
                    problem.DueTime[i] = rand.Next((int)Math.Ceiling(problem.GetDistance(0, i, null)), 1200);
                    problem.ReadyTime[i] = problem.DueTime[i] - rand.Next(0, 100);
                    problem.ServiceTime[i] = 90;
                }
            }

            this.ProblemInstance = problem;
        }

        public void ImportSolution(string solutionFileName)
        {
            SolutionParser parser = new SolutionParser(solutionFileName);
            parser.Parse();

            HeuristicLab.Problems.VehicleRouting.Encodings.Potvin.PotvinEncoding encoding = new Encodings.Potvin.PotvinEncoding(ProblemInstance);

            int cities = 0;
            foreach (List<int> route in parser.Routes)
            {
                Tour tour = new Tour();
                tour.Stops.AddRange(route);
                cities += tour.Stops.Count;

                encoding.Tours.Add(tour);
            }

            if (cities != ProblemInstance.Coordinates.Rows - 1)
                ErrorHandling.ShowErrorDialog(new Exception("The optimal solution does not seem to correspond with the problem data"));
            else
            {
                VRPSolution solution = new VRPSolution(ProblemInstance, encoding, new DoubleValue(0));
                BestKnownSolutionParameter.Value = solution;
            }
        }

        #region Instance Consuming
        public void Load(IPSPPData data, IPSPPDataInterpreter interpreter)
        {
            PSPPInstanceDescription instance = interpreter.Interpret(data);

            Name = instance.Name;
            Description = instance.Description;

            BestKnownQuality = null;
            BestKnownSolution = null;

            if (ProblemInstance != null && instance.ProblemInstance != null &&
              instance.ProblemInstance.GetType() == ProblemInstance.GetType())
                SetProblemInstance(instance.ProblemInstance);
            else
                ProblemInstance = instance.ProblemInstance;

            OnReset();

            if (instance.BestKnownQuality != null)
            {
                BestKnownQuality = new DoubleValue((double)instance.BestKnownQuality);
            }

            if (instance.BestKnownSolution != null)
            {
                PSPPSolution solution = new PSPPSolution(ProblemInstance, instance.BestKnownSolution, new DoubleValue(0));
                BestKnownSolution = solution;
            }
        }
        #endregion

        #region IProblemInstanceConsumer<VRPData> Members

        public void Load(IPSPPData data)
        {
            var interpreterDataType = data.GetType();
            var interpreterType = typeof(IPSPPDataInterpreter<>).MakeGenericType(interpreterDataType);

            var interpreters = ApplicationManager.Manager.GetTypes(interpreterType);

            var concreteInterpreter = interpreters.Single(t => GetInterpreterDataType(t) == interpreterDataType);

            Load(data, (IPSPPDataInterpreter)Activator.CreateInstance(concreteInterpreter));
        }

        private Type GetInterpreterDataType(Type type)
        {
            var parentInterfaces = type.BaseType.GetInterfaces();
            var interfaces = type.GetInterfaces().Except(parentInterfaces);

            var interpreterInterface = interfaces.Single(i => typeof(IPSPPDataInterpreter).IsAssignableFrom(i));
            return interpreterInterface.GetGenericArguments()[0];
        }

        #endregion
    }
}
