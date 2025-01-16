import sys
import os

def update_connector_build_num(file_path, new_build_num):
    # Read the file contents
    with open(file_path, 'r', encoding='utf-8') as file:
        file_contents = file.read()

    # Replace all occurrences of "connector_build_num" with the new build number
    updated_contents = file_contents.replace('"connector_build_num"', f'"{new_build_num}"')

    # If the content has been updated, write it back to the file
    if updated_contents != file_contents:
        with open(file_path, 'w', encoding='utf-8') as file:
            file.write(updated_contents)
        print(f"Connector build number updated to: {new_build_num}")
    else:
        print("No changes made. Could not find the connector build number in the file.")

def main():
    # Check if we have the correct number of command-line arguments
    if len(sys.argv) != 2:
        print("Usage: python versioning.py <new_build_num>")
        sys.exit(1)

    # Get the new build number from the command line argument
    new_build_num = sys.argv[1]

    # Define the relative path to the AddOn.grc file from the script's location
    script_dir = os.path.dirname(os.path.abspath(__file__))
    # Move one folder up and construct the path to the AddOn.grc file
    file_path = os.path.join(script_dir, '..', 'AddOns', 'Speckle', 'Sources', 'AddOnResources', 'RINT', 'AddOn.grc')

    # Resolve the final absolute file path
    file_path = os.path.abspath(file_path)

    # Check if the file exists
    if not os.path.isfile(file_path):
        print(f"File not found: {file_path}")
        sys.exit(1)

    # Update the connector build number
    update_connector_build_num(file_path, new_build_num)

if __name__ == "__main__":
    main()
