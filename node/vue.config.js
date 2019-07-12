const VuetifyLoader = require('vuetify-loader/lib/plugin');
const path = require('path');

module.exports = {
  chainWebpack (config) {
    config
      .plugin('vuetify-loader')
      .use(VuetifyLoader);

    config.module
      .rule('fonts')
      .use('url-loader')
      .options({
        limit: 4096,
        fallback: {
          loader: 'file-loader',
          options: {
            name: 'fonts/[hash:8].[ext]'
          }
        }
      });
  },
  outputDir: path.resolve(__dirname, '../data')
};
