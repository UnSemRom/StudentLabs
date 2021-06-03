import Vue from 'vue'
window.axios = require('axios');
import Vuelidate from 'vuelidate'
import App from '@/views/App/index.vue'
import router from './router'
import store from './store'
import AxiosPlugin from 'vue-axios-cors';
import './assets/main.scss'
Vue.config.productionTip = false;




Vue.use(Vuelidate);
Vue.use(AxiosPlugin)


new Vue({
  router,
  store,
  render: h => h(App)
}).$mount('#app')