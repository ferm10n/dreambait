import Vue from 'vue';
import 'vuetify/src/stylus/app.styl';
import Vuetify from 'vuetify/lib';
import App from './App.vue';
import 'material-design-icons-iconfont/dist/material-design-icons.css';

// import { library } from '@fortawesome/fontawesome-svg-core';
// import { FontAwesomeIcon } from '@fortawesome/vue-fontawesome';
// import { fas } from '@fortawesome/free-solid-svg-icons';

// Vue.component('font-awesome-icon', FontAwesomeIcon); // Register component globally
// library.add(fas); // Include needed icons.

// Vue.use(Vuetify, {
//   iconfont: 'faSvg'
// });
Vue.use(Vuetify);

new Vue(App); // eslint-disable-line no-new
