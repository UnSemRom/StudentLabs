import $http from '@/api';
import {
  setToken,
  deleteToken,
  getToken,
} from '@/utils/token';

export default {
  namespaced: true,
  state: {
    token: getToken($http),
  },

  getters: {
    isAuthenticated(state) {
      const isTokenExists = !!state.token;

      return isTokenExists;
    },
  },

  mutations: {
    ['AUTH']: (state, token) => {
      state.token = token;
    },
    ['LOGOUT']: (state) => {
      state.token = '';
    },
  },

  actions: {
    async login({ commit }, { mail, password, rememberMe }) {
      try {
        const { data } = await $http.post('/login', {
          mail,
          password,
        });
        const token = data.access_token;

        rememberMe ? setToken('local', token, $http) : setToken('session', token, $http);

        commit('AUTH', token);

        return { data };
      } catch {
        console.log("Ошибка со входом")
      }
    },
    
    async register({ commit }, { name, mail, password, rememberMe }) {
      try {
        const { data } = await $http.post('/register', {
          name,
          mail,
          password,
        });
        const token = data.access_token;

        setToken('local', token, $http);

        commit('AUTH', token);

        return { data };
      } catch {
        console.log("Ошибка с регистрацией")
      }
    },
    
    logout({ commit }) {
      deleteToken($http);
      commit('LOGOUT');
      return;
    },
  },
};