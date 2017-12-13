'use strict'
const express = require('express')
const app = express()
var cors = require('cors');
const msg = "Hello from CAT's backend server!";
/*app.get('/', (req, res) => {
    res.sendFile(`${__dirname}/index.html`)
})*/

app.use(cors());

app.get('/', (request, response) => {
  response.json({
    greeting: msg
  })
})

app.get('/cat', (request, response) => {
  response.json({
    greeting: "meow"
  })
})

//app.listen(3000) // <-- uncomment for local testing

module.exports = app // export your app so aws-serverless-express can use it
