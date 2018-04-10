# awslambda

[![Greenkeeper badge](https://badges.greenkeeper.io/vitarn/awslambda.svg)](https://greenkeeper.io/)
Download from AWS Lambda runtime environment.

Current version: 0.3.0

Lambda run this module like this:

```console
/var/lang/bin/node /var/runtime/node_modules/awslambda/index.js --expose-gc --max-executable-size=13 --max-semi-space-size=6 --max-old-space-size=102
```

The entry `index.js` run your function similar this:

```js
require('/var/task/handler')['function'](event, context, callback)
```
