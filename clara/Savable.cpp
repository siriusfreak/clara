#include "Savable.h"


String Savable::GetFileName() {
	return this->Device + "_" + this->ID + ".json";
}

template<typename   T> T Savable::GetOrDefault(String name, std::vector<String> &param, std::vector<String> &value, T def) {
	int ind = -1;

	for (int i = 0; i < param.size(); i++)
		if (param[i] == name) {
			ind = i;
			break;
		}

	T res = def;
	if (ind != -1)
		res = dynamic_cast<T>(value[ind]);
	return res;
}

void Savable::SaveJson() {
	File file = SPIFFS.open(this->GetFileName(), "w");
	if (file) {
		String json = this->GetJson();
		static unsigned char buf[Savable::maxBufSize];

		json.getBytes(buf, Savable::maxBufSize);

		file.write(buf, Savable::maxBufSize);

		file.close();
	}
}

void Savable::LoadFromJson() {
	static StaticJsonBuffer<Savable::maxBufSize> jsonBuffer;
	static char buf[Savable::maxBufSize];

	File file = SPIFFS.open(this->GetFileName(), "r");
	if (file) {
		size_t size = file.size();
		if (size != 0 && size <= Savable::maxBufSize) {

			file.readBytes(buf, size);
			JsonObject& root = jsonBuffer.parseObject(buf);
			if (root.success()) {
				std::vector<String> params(root.size());
				std::vector<String> values(root.size());

				int ind = 0;
				for (JsonObject::iterator it = root.begin(); it != root.end(); ++it, ind++) {
					params[ind] = String(it->key);
					values[ind] = String(it->value.asString());
				}

				this->LoadFromParams(params, values);
			}
		}
		file.close();
	}
}
