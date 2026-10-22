from src.ImageResourceGenerator.SvgProcessor import SvgProcessor

import json
import sys


def ParseArguments():
    import argparse

    parser = argparse.ArgumentParser(
        description="Converts SVG files to dark mode compatible SVG resources, based on a color configuration file."
    )
    parser.add_argument("--inputFile", type=str, required=True, help="Input svg file for color change")
    parser.add_argument("--outputFile", type=str, required=True, help="Output file for generated svg resources")
    parser.add_argument("--colorConfig", type=str, required=True, help="Path to color configuration json file")
    return parser.parse_args()


def Main():
    args = ParseArguments()

    with open(args.colorConfig, "r", encoding="utf-8", errors="strict") as f:
        colorConfig = json.load(f)

    svgProcessor = SvgProcessor(colorConfig)
    darkModeSVGBytes, unexpectedColors = svgProcessor.DoColorCheck(args.inputFile, withColorChange=True)

    if unexpectedColors:
        print(f"SVG contains unexpected color(s): {unexpectedColors} - {args.inputFile}", file=sys.stderr)

    with open(args.outputFile, "wb") as f:
        f.write(darkModeSVGBytes)


if __name__ == "__main__":
    Main()