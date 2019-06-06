const path = require('path');
const HtmlWebpackPlugin = require('html-webpack-plugin');
const outputDir = path.join(__dirname, 'build/');

const isProd = process.env.NODE_ENV === 'production';

module.exports = {
  entry: './src/entry.js',
  mode: isProd ? 'production' : 'development',
  resolveLoader: {
    modules: [path.resolve(__dirname, 'src/webpack'), 'node_modules']
  },
  output: {
    path: outputDir,
    filename: 'index.js'
  },
  plugins: [
    new HtmlWebpackPlugin({
      template: 'src/index.html',
      inject: false
    })
  ],
  module: {
    rules: [
      {
        test: /\.(js|jsx)$/,
        exclude: /node_modules/,
        use: ['babel-loader']
      },
      {
        test: /\.css$/,
        use: ['style-loader', 'css-loader']
      },
      {
        test: /\.(woff(2)?|ttf|eot|svg)(\?v=\d+\.\d+\.\d+)?$/,
        use: [
          {
            loader: 'file-loader',
            options: {
              name: '[name].[ext]',
              outputPath: 'fonts/'
            }
          }
        ]
      },
      {
        test: /\.png$/,
        use: ['file-loader', 'image-webpack-loader']
      },
      {
        test: /\.ml$/,
        use: ['json-loader', 'code-loader']
      }
    ]
  },
  // resolve: {
  //   extensions: ['*', '.js', '.jsx']
  // },
  devServer: {
    compress: true,
    contentBase: outputDir,
    port: process.env.PORT || 8000,
    historyApiFallback: true
  }
};
