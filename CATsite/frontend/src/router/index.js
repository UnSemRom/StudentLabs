import Vue from 'vue'
import VueRouter from 'vue-router'

Vue.use(VueRouter)

import { mainNav } from './mainNav';
import { authNav } from './authNav';

export const routes = [
  ...mainNav,
  ...authNav,
];

const router = new VueRouter({
  mode: 'history',
  base: process.env.BASE_URL,
  routes
})

export default router
