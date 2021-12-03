using System;

namespace SWO5.Dashboard.Domain
{
    public class State
    {
        public long Id { get; set; }
        public string Name { get; set; }

        public override string ToString()
        {
            return $"{Name}";
        }

        public override bool Equals(object obj)
        {
            State state = obj as State;
            return state != null && state.Name.Equals(this.Name);
        }
    }
    public class District
    {
        public long Id { get; set; }
        public State ResponsibleState { get; set; }
        public string Name { get; set; }

        public long Population { get; set; }

        public override string ToString()
        {
            return $"{Name} ({ResponsibleState})";
        }

    }

    public class User
    {
        public long Id { get; set; }
        public string Name { get; set; }
        public string Password { get; set; }
    }

    public class Report
    {
        public long Id { get; set; }
        public DateTime Date { get; set; }
        public District ResponsibleDistrict { get; set; }
        public long Infected { get; set; }
        public long Recovered { get; set; }
        public long Deceased { get; set; }
        public long Incidence { get; set; }

        public override string ToString()
        {
            return $"{ResponsibleDistrict}:\n" +
                    $"Infected: {Infected},\n" +
                    $"Recovered: {Recovered},\n" +
                    $"Deceased: {Deceased},\n" +
                    $"Incidence: {Incidence}";
        }
    }
}
