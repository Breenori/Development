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
            return state != null && (state.Id.Equals(this.Id) && state.Name.Equals(this.Name));
        }

        public override int GetHashCode()
        {
            return Id.GetHashCode() + Name.GetHashCode();
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

        // override object.Equals
        public override bool Equals(object obj)
        {
            District district = obj as District;
            return district != null && district.Id.Equals(this.Id) && district.Name.Equals(this.Name);
        }

        // override object.GetHashCode
        public override int GetHashCode()
        {
            return Id.GetHashCode() + Name.GetHashCode();
        }

    }

    public class User
    {
        public long Id { get; set; }
        public string Name { get; set; }
        public string Password { get; set; }

        public override string ToString()
        {
            return Name;
        }

        // override object.Equals
        public override bool Equals(object obj)
        {
            User user = obj as User;
            return user != null && (user.Id.Equals(this.Id) || user.Name.Equals(this.Name));
        }

    }

    public class Report
    {
        public long Id { get; set; }
        public DateTime Date { get; set; }
        public District ResponsibleDistrict { get; set; }
        public long Infected { get; set; }
        public long Recovered { get; set; }
        public long Deceased { get; set; }
        public double Incidence { get; set; }

        public User FromUser { get; set; }
        public override string ToString()
        {
            return $"{ResponsibleDistrict}:\n" +
                    $"Infected: {Infected},\n" +
                    $"Recovered: {Recovered},\n" +
                    $"Deceased: {Deceased},\n" +
                    $"Incidence: {Incidence}";
        }

        public override bool Equals(object obj)
        {
            Report report = obj as Report;
            return report != null && (report.Id.Equals(this.Id));
        }
    }
}
