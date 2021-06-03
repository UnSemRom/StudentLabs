import Registration from '@/views/Auth/Registration'
import Login from '@/views/Auth/Login'
const authNav = [
    {
        path: '/registration',
        name: 'registration',
        component: Registration
      },
      {
        path: '/login',
        name: 'login',
        component: Login
      },
  ];
  
  export { authNav };