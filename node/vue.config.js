const VuetifyLoader = require('vuetify-loader/lib/plugin');
const path = require('path');

module.exports = {
  chainWebpack (config) {
    config
      .plugin('vuetify-loader')
      .use(VuetifyLoader);
  },
  outputDir: path.resolve(__dirname, '../data')
};
