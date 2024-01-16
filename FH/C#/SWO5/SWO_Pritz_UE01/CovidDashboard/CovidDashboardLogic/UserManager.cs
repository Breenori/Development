using SWO5.Dashboard.DAL;
using SWO5.Dashboard.DAL.SQLe;
using SWO5.Dashboard.Domain;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SWO5.Dashboard.Logic
{
    class UserManager : IManager<User>
    {
        private IUserDao userDao = DaoFactorySQLe.UserDao;

        public User Create(User entity)
        {
            entity.Id = userDao.Create(entity);
            return entity;
        }

        public bool Delete(User entity)
        {
            return userDao.Delete(entity);
        }

        public IList<User> FindAll()
        {
            return userDao.ReadAll();
        }

        public User FindById(long identity)
        {
            return userDao.ReadForIdentity(identity);
        }

        public User Update(User entity)
        {
            entity.Id = userDao.Update(entity);
            return entity;
        }
    }
}
