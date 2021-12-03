using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SWO5.Currency.DAL
{
    public interface IDao<T>
    {

        T ReadForIdentity(long identity);

        IList<T> ReadAll();

        long Create(T entity);

        long Update(T entity);

        bool Delete(long id);
    }
}
