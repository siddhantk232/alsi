{
  description = "A very basic flake";

  outputs = { self, nixpkgs }:
  let
    system = "x86_64-linux";
    pkgs = import nixpkgs { inherit system; };
  in
  {
    devShells.${system}.default = pkgs.mkShell {
        name = "alsi-shell";
        buildInputs = with pkgs; [
          SDL2
          SDL2_image
          SDL2_ttf
          pkg-config
        ];
        CFLAGS = [
            "-I${pkgs.SDL2_image}/include/SDL2"
            "-I${pkgs.SDL2_ttf}/include/SDL2"
            "-I${pkgs.SDL2.dev}/include/SDL2"
        ];
      };
  };
}

