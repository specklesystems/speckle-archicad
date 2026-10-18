import re
import codecs

from pathlib import Path

class SvgProcessor():
	def __init__(self, colorConfig):
		self.colorTable 		= colorConfig["colorTable"]
		self.noCheckFiles 		= colorConfig["noCheckFiles"]
		self.noCheckFolders 	= colorConfig["noCheckFolders"]
		self.excludeFiles 		= colorConfig["excludeFiles"]
		self.excludeFolders 	= colorConfig["excludeFolders"]
		self.colorReplacerRegEx = re.compile("(%s)" % "|".join(map(re.escape, self.colorTable.keys())), re.IGNORECASE)
		self.colorCheckerRegEx	= re.compile("(#[A-F0-9]{6}|#[A-F0-9]{3})", re.IGNORECASE)

	def ColorsCheck(self, svgContent):
		colorsInSvg = re.findall(self.colorCheckerRegEx, svgContent)
		unexpectedColors = []
		for colorInSvg in colorsInSvg:
			if not colorInSvg.upper() in self.colorTable.keys():
				unexpectedColors.append(colorInSvg)
		return unexpectedColors

	def DoColorCheck(self, imageFilePath, withColorChange = True):
		with codecs.open(imageFilePath, encoding="utf-8", errors="ignore") as f:
			svgContent = f.read()
		darkModeSVGBytes = str.encode(svgContent)
		unexpectedColors = []

		fileName = Path(imageFilePath).stem
		isExcluded = bool(fileName in self.excludeFiles or list(set(Path(imageFilePath).parts) & set(self.excludeFolders)))
		if not isExcluded:
			isColorCheckNeeded = bool(fileName not in self.noCheckFiles and not list(set(Path(imageFilePath).parts) & set(self.noCheckFolders)))
			if isColorCheckNeeded:
				unexpectedColors = self.ColorsCheck(svgContent)
			if withColorChange:
				svgContent = self.colorReplacerRegEx.sub(lambda color:
								self.colorTable[color.string[color.start():color.end()].upper()], svgContent)
				darkModeSVGBytes = str.encode(svgContent)
		return darkModeSVGBytes, unexpectedColors

	def saveAsPng(self, pngName : str, image):
		png_info = image.info
		image.save(pngName, format = "PNG", **png_info)
