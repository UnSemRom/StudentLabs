import $http from '@/api';


const SET_FILE = 'SET_FILE';

export default {
    namespaced: true,
    state: {
        files: [],
    },
    mutations: {
        [SET_FILE](state, payload) {
            state.files.push(payload)
        },
    },
    actions: {
        async setFILE(context, file) {
            context.commit('SET_FILE', file);
        },
    },
    getters: {
        getAllFiles(state) {
            return state
        }
    }
};