git clone https://github.com/wenyi5608/GroundingDINO.git -b wenyi5608-openvino /workspaces/otus-cpp-basics-final-project/repos/GroundingDINO
cd /workspaces/otus-cpp-basics-final-project/repos/GroundingDINO/
pip install -r requirements.txt
pip install -e .

cd /workspaces/otus-cpp-basics-final-project
mkdir /workspaces/otus-cpp-basics-final-project/weights
wget -q https://github.com/IDEA-Research/GroundingDINO/releases/download/v0.1.0-alpha/groundingdino_swint_ogc.pth -P /workspaces/otus-cpp-basics-final-project/weights/

python3 /workspaces/otus-cpp-basics-final-project/scripts/gdino2onnx.py \
        -c /workspaces/otus-cpp-basics-final-project/repos/GroundingDINO/groundingdino/config/GroundingDINO_SwinT_OGC.py \
        -p /workspaces/otus-cpp-basics-final-project/weights/groundingdino_swint_ogc.pth \
        -o /workspaces/otus-cpp-basics-final-project/weights/
