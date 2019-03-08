const VuetifyLoader = require('vuetify-loader/lib/plugin');

module.exports = {
  chainWebpack (config) {
    config
      .plugin('vuetify-loader')
      .use(VuetifyLoader);
  }
};
