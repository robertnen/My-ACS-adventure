from .map import Map

from typing import List, Union
import imageio
import glob
import os
import re

__all__ = ['save_images', 'create_gif']


def save_images(solution_steps: List[Union[str, Map]], save_path: str) -> None:
    for i, step in enumerate(solution_steps):

        if step is None:
            continue

        if isinstance(step, str):
            state = Map.from_str(step)
        else:
            state = step
            
        state.save_map(save_path, f"step{i}.png")


def create_gif(path_images, gif_name, save_path):
    images_paths = glob.glob(f'{path_images}/*.png')

    # Steps: extract filename -> remove .png -> remove non digit characters -> convert to int
    key = lambda path: int(re.sub(r'\D', '', os.path.basename(path).split('.')[0]))
    images_paths = sorted(images_paths, key=key)  # Sort the frames based on the exploration step order

    if '.gif' not in gif_name:
        gif_name += '.gif'

    if not os.path.exists(save_path):
        os.makedirs(save_path)

    if os.path.exists(f'{save_path}/{gif_name}'):
        os.remove(f'{save_path}/{gif_name}')

    imageio.plugins.freeimage.download()

    images = []
    for filename in images_paths:
        # Tick rate of 0.1 seconds
        images.append(imageio.imread(filename))

    imageio.mimsave(f'{save_path}/{gif_name}', images, 'GIF-FI', duration=0.5)
    print(f"GIF saved at: {f'{save_path}/{gif_name}'}")
