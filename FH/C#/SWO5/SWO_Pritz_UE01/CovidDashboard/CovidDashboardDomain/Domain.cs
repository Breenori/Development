using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.ComponentModel.DataAnnotations;
using System.ComponentModel.DataAnnotations.Schema;

namespace SWO5.Dashboard.Domain
{
    public class State
    {
        public long Id { get; set; }
        [Required(ErrorMessage = "A state name is required."), MinLength(2, ErrorMessage = "State name must have at least 2 characters."), MaxLength(50, ErrorMessage = "Please keep the state name below 50 characters.")]
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
        [Required(ErrorMessage = "A district name is required."), MinLength(2, ErrorMessage = "District name must have at least 2 characters."), MaxLength(50, ErrorMessage = "Please keep the district name below 50 characters.")]
        public string Name { get; set; }
        [Required, Range(0,long.MaxValue, ErrorMessage = "Population can't reach negative digits.")]
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
        [Required(ErrorMessage ="A username is required."), MinLength(2, ErrorMessage = "Username must have at least 2 characters."), MaxLength(50, ErrorMessage = "Please keep the username below 50 characters.")]
        public string Name { get; set; }
        [Required(ErrorMessage = "A password is required."), MinLength(6, ErrorMessage = "Password must have at least 6 characters.")]
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
        [Required(ErrorMessage = "Setting a district is required.")]
        public District ResponsibleDistrict { get; set; }
        [Required(ErrorMessage = "Setting the number of infected is required."), Range(0, long.MaxValue, ErrorMessage = "Infected can't reach negative digits.")]
        public long Infected { get; set; }
        [Required(ErrorMessage = "Setting the number of recovered is required."), Range(0, long.MaxValue, ErrorMessage = "Recovered can't reach negative digits.")]
        public long Recovered { get; set; }
        [Required(ErrorMessage = "Setting the number of deceased is required."), Range(0, long.MaxValue, ErrorMessage = "Deceased can't reach negative digits.")]
        public long Deceased { get; set; }
        [Required(ErrorMessage = "Setting the incidence is required."), Range(0, double.MaxValue, ErrorMessage = "Incidence can't reach negative digits.")]
        public double Incidence { get; set; }

        [Required(ErrorMessage = "Setting a user is required.")]
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
