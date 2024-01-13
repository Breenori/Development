using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SWO5.Dashboard.DAL
{
    public interface IDao<T>
    {
        T ReadForIdentity(long identity);
        IList<T> ReadAll();
        long Create(T entity);
        long Update(T entity);
        bool Delete(T entity);
        // I also decided to include DROP to make it easier to re-load the data from a CSV
        void Drop();
    }
}
