const fs = require('fs')

const Command = {
  put: {symbol: Symbol('Put'), hasArg: true},
  hide: {symbol: Symbol('Hide'), hasArg: false},
  show: {symbol: Symbol('Show'), hasArg: false},
  region: {symbol: Symbol('Region'), hasArg: true}
}

const not = (f, x) => !f(x)
const equal = (a, b) => a === b
const inRange = (a, b, c) => a <= c && c <= b
const charCode = (c) => c.charCodeAt(0)

const isWhitespace = equal.bind(null, ' ')
const isAlpha = (c) => inRange(charCode('a'), charCode('z'), charCode(c))

const upperCamelCase = function(str) {
  if(str === null || str.length === 0) return str
  let result = str.slice()
  result[0] = result[0].toUpperCase()
  return result
}

const skipWhile = function(f, buf) {
  while(f(buf.data[buf.index])) buf.index++
}
const takeWhile = function(f, buf) {
  let start = buf.index
  skipWhile(f, buf)
  return buf.data.slice(start, buf.index)
}

const skipWhitespace = skipWhile.bind(null, isWhitespace)
const readWord = takeWhile.bind(null, isAlpha)
const readArgument = takeWhile.bind(null, not.bind(null, equal.bind(null, '*')))

const eat = function(buf, str) {
  for(var i = 0; i < str.length; i++)
    if(buf.data[buf.index+i] !== str[i]) return false
  buf.index += str.length
  return true
}

const parseCommand = function(line) {
  let buf = {data: line, index: 0}
  skipWhitespace(buf)
  if(!eat(buf, '(*')) return null
  skipWhitespace(buf)
  if(!eat(buf, '$')) return null
  
  let word = readWord(buf)
  let commandType = Command[word]
  if(commandType === undefined || commandType === null) throw 'invalid command'

  let arg = undefined
  if(commandType.hasArg) {
    skipWhitespace(buf)
    arg = readArgument(buf)
  }
  skipWhitespace(buf)
  if(!eat(buf, '*)')) throw 'invalid syntax'
  return {tag: commandType.symbol, arg: arg}
}

// TODO: fix region calculations (currently requires new line separation between regions + new line at end of file; should calculate based on empty lines)
module.exports = function(src) {
  let showing = true
  let lineNumber = 1
  let rangeStart = 0
  let rangeTitle = undefined
  let ranges = []
  let processedLines = []

  const pushLine = (line) => {
    lineNumber++
    processedLines.push(line)
  }

  const pushRegion = (title) => {
    if(lineNumber-1 !== rangeStart) {
      ranges.push({loc: [rangeStart, lineNumber-2], title: rangeTitle})
      rangeStart = lineNumber-1
    }
    rangeTitle = title
  }

  src.split('\n').forEach(function(line) { 
    const command = parseCommand(line)
    if(command !== null) {
      switch(command.tag) {
      case Command.put.symbol: pushLine(command.arg); break
      case Command.hide.symbol: showing = false; break
      case Command.show.symbol: showing = true; break
      case Command.region.symbol: pushRegion(command.arg); break
      default: throw 'unhandled command'
      }
    } else {
      if(showing) {
        pushLine(line)
      } else {
        return false
      }
    }
  })

  // pushRegion()
  ranges.push({loc: [rangeStart, lineNumber-2], title: rangeTitle})
  console.log(JSON.stringify(ranges))
  return JSON.stringify({source: processedLines.join('\n'), ranges: ranges})
}
